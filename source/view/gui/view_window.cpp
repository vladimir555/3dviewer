#include "view_window.h"


#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QForwardRenderer>

namespace view::gui {


static int  const DEFAULT_WINDOW_WIDTH      = 640;
static int  const DEFAULT_WINDOW_HEIGHT     = 480;
static char const DEFAULT_WINDOW_TITLE[]    = "3D View";


CViewWindow::CViewWindow(controller::IViewer::TPtr const &player) {
    resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    setWindowTitle(tr(DEFAULT_WINDOW_TITLE));

    auto view               = new Qt3DExtras::Qt3DWindow();
    auto scene              = new Qt3DCore::QEntity();
    auto cylinder_entity    = new Qt3DCore::QEntity(scene);
    auto cylinder_mesh      = new Qt3DExtras::QCylinderMesh;

    cylinder_mesh->setRadius(1.0f);
    cylinder_mesh->setLength(3.0f);
    cylinder_mesh->setRings(100);
    cylinder_mesh->setSlices(8);

    auto cylinder_material  = new Qt3DExtras::QPhongMaterial;
    cylinder_material->setDiffuse(QColor(QRgb(0x00FF00)));

    cylinder_entity->addComponent(cylinder_mesh);
    cylinder_entity->addComponent(cylinder_material);

    m_object_transform = new Qt3DCore::QTransform();
    cylinder_entity->addComponent(m_object_transform);

    auto camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition     (QVector3D(0, 0, 20.0f));
    camera->setViewCenter   (QVector3D(0, 0, 0));

    auto camera_controller  = new Qt3DExtras::QOrbitCameraController(scene);
    camera_controller->setCamera(camera);

    view->defaultFrameGraph()->setClearColor(palette().color(QPalette::Window));

    view->setRootEntity(scene);
    auto container          = QWidget::createWindowContainer(view);
    setCentralWidget(container);

    // object rotating ticker
    {
        auto timer = new QTimer();
        timer->setInterval(1000 / 5);
        connect(timer, &QTimer::timeout, this, &CViewWindow::onTimerTick);
        timer->start();
    }
}


void CViewWindow::closeEvent(QCloseEvent *event) {
    QCoreApplication::quit();
    QMainWindow::closeEvent(event);
}


void CViewWindow::onTimerTick() {
     m_angle += 5.0f;
     if (m_angle >= 360.0f)
         m_angle -= 360.0f;

     m_object_transform->setRotation(QQuaternion::fromEulerAngles(m_angle, 0.0f, 0.0f));
}


} // view::gui
