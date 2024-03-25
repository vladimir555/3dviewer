#include "scene.h"


namespace controller::implementation {


CScene::CScene(view::ISettings *settings, view::IViewer *viewer) {
//    QObject::connect(settings, &view::ISettings::onSceneUpdated, viewer, &view::IViewer::onSceneUpdated);
//    connect(dynamic_cast<QObject*>(es), SIGNAL(someThingHappended()), ...);
    connect(
        dynamic_cast<QObject *>(settings), SIGNAL(onSceneUpdated),
        dynamic_cast<QObject *>(viewer)  , SLOT  (onSceneUpdated));
}


} // controller::implementation
