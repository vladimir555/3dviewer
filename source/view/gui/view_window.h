#pragma once


#include "view/view.h"

#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QMainWindow>
#include <QTimer>
#include <Qt3DCore/QTransform>


namespace view::gui {


class CViewWindow: public QMainWindow, public IViewer {
    Q_OBJECT
public:
    typedef QSharedPointer<CViewWindow> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }
    
    CViewWindow();
    virtual ~CViewWindow() = default;

public slots:
    void onSceneUpdated     (model::IScene::TPtr    const &scene)       override;
    void onCylinderUpdated  (model::ICylinder::TPtr const &cylinder)    override;

private:
    void closeEvent(QCloseEvent *event) override;

    void onTimerTick();

    Qt3DCore::QTransform   *m_object_transform = nullptr;
    float                   m_angle = 0.0f;
};


} // view::gui
