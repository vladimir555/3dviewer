#include "view_window.h"


#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>

namespace view::gui {


static int  const DEFAULT_WINDOW_WIDTH                  = 640;
static int  const DEFAULT_WINDOW_HEIGHT                 = 480;
static char const DEFAULT_WINDOW_TITLE[]                = "3D View";
static int  const DEFAULT_FRAME_INTERVAL_MS             = 1000 / 60;
static int  const DEFAULT_ROTATION_SPEED_DEGREES_PER_MS = 1;


CViewWindow::CViewWindow() {
    resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    setWindowTitle(tr(DEFAULT_WINDOW_TITLE));

    m_rotation_axis = model::IScene::TRotationAxis::X;

    updateScene();

    // object rotating ticker
    {
        auto timer = new QTimer();
        timer->setInterval(DEFAULT_FRAME_INTERVAL_MS);
        connect(timer, &QTimer::timeout, this, &CViewWindow::onTimerTick);
        timer->start();
    }
}


void CViewWindow::onSceneUpdated(model::IScene::TPtr const &scene) {
    if (scene) {
        QMutexLocker lock(&m_mutex);
        m_scene = scene;
        updateScene();
    }
    qDebug() << "CViewWindow::onSceneUpdated";
}


void CViewWindow::onCylinderUpdated(model::ICylinder::TPtr const &cylinder) {
    if (cylinder) {
        QMutexLocker lock(&m_mutex);
        m_cylinder = cylinder;
        updateScene();
    }
    qDebug() << "CViewWindow::onCylinderUpdated";
}


void CViewWindow::closeEvent(QCloseEvent *event) {
    QCoreApplication::quit();
    QMainWindow::closeEvent(event);
}


void CViewWindow::onTimerTick() {
    static float DEFAULT_MAX_ANGLE = 360.0f;

    QMutexLocker lock(&m_mutex);

     m_angle += DEFAULT_ROTATION_SPEED_DEGREES_PER_MS;
     if (m_angle >= DEFAULT_MAX_ANGLE)
         m_angle -= DEFAULT_MAX_ANGLE;

    switch (m_rotation_axis) {
        case model::IScene::TRotationAxis::X:
            m_object_transform->setRotationX(m_angle);
            break;

        case model::IScene::TRotationAxis::Y:
            m_object_transform->setRotationY(m_angle);
            break;

        case model::IScene::TRotationAxis::Z:
            m_object_transform->setRotationZ(m_angle);
            break;

        default:
            break;
    }
}


void CViewWindow::updateScene() {
    auto scene  = new Qt3DCore::QEntity();
    auto entity = new Qt3DCore::QEntity(scene);
    auto mesh   = new Qt3DExtras::QCylinderMesh;
    auto view   = new Qt3DExtras::Qt3DWindow();

    mesh->setRadius(1.0f);
    mesh->setLength(3.0f);
    mesh->setRings(100);

    if (m_cylinder)
        mesh->setSlices(static_cast<int>(m_cylinder->getVerticesNumber()));
    else
        mesh->setSlices(5);

    auto material = new Qt3DExtras::QPhongMaterial();
    if (m_cylinder)
        material->setDiffuse(m_cylinder->getColor());
    else
        material->setDiffuse(QColor(QRgb(0xFF0000)));

    entity->addComponent(mesh);
    entity->addComponent(material);

    auto object_transform   = new Qt3DCore::QTransform();
    entity->addComponent(object_transform);

    auto camera = view->camera();
    camera->setPosition     (QVector3D(0, 0, 20.0f));
    camera->setViewCenter   (QVector3D(0, 0, 0));
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);

    auto camera_controller  = new Qt3DExtras::QOrbitCameraController(scene);
    camera_controller->setCamera(camera);

    view->defaultFrameGraph()->setClearColor(palette().color(QPalette::Window));

    view->setRootEntity(scene);
    auto container          = QWidget::createWindowContainer(view);
    setCentralWidget(container);

    if (m_scene)
        m_rotation_axis = m_scene->getRotationAxys();

    m_object_transform = object_transform;
}


} // view::gui
