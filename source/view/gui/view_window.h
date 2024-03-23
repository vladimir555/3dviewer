#pragma once


#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <QMainWindow>
#include <QTimer>
#include <Qt3DCore/QTransform>

#include "controller/viewer.h"


namespace view::gui {


class CViewWindow: public QMainWindow {
    Q_OBJECT
public:
    typedef QSharedPointer<CViewWindow> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }
    
    CViewWindow(controller::IViewer::TPtr const &viewer);
    virtual ~CViewWindow() = default;

private:
    void closeEvent(QCloseEvent *event) override;

    void onTimerTick();

    Qt3DCore::QTransform   *m_object_transform = nullptr;
    float                   m_angle = 0.0f;
};


} // view::gui
