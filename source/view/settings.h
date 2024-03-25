#pragma once


#include "model/cylinder.h"
#include "model/scene.h"

#include <QObject>


namespace view {


class ISettings/*: public QObject*/ {
//    Q_OBJECT
public:
    virtual ~ISettings() = default;
signals:
    virtual void onSceneUpdated     (model::IScene::TPtr    const &scene)       = 0;
    virtual void onCylinderUpdated  (model::ICylinder::TPtr const &cylinder)    = 0;
};


} // view::gui


Q_DECLARE_INTERFACE(view::ISettings, "view::ISettings")
