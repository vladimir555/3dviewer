#include "scene.h"


#include "view/gui/settings_window.h"
#include "view/gui/view_window.h"


namespace controller::implementation {


CScene::CScene(view::ISettings *settings, view::IViewer *viewer) {
    connect(
        dynamic_cast<view::gui::CSettingsWindow *>(settings), &view::gui::CSettingsWindow::onSceneUpdated,
        dynamic_cast<view::gui::CViewWindow     *>(viewer)  , &view::gui::CViewWindow::onSceneUpdated);

    connect(
        dynamic_cast<view::gui::CSettingsWindow *>(settings), &view::gui::CSettingsWindow::onCylinderUpdated,
        dynamic_cast<view::gui::CViewWindow     *>(viewer)  , &view::gui::CViewWindow::onCylinderUpdated);

//    connect(
//        dynamic_cast<QObject *>(settings), SIGNAL(view:: onSceneUpdated),
//        dynamic_cast<QObject *>(viewer)  , SLOT  (onSceneUpdated));
//    connect(
//        dynamic_cast<QObject *>(settings), SIGNAL(onCylinderUpdated),
//        dynamic_cast<QObject *>(viewer)  , SLOT  (onCylinderUpdated));
}


} // controller::implementation
