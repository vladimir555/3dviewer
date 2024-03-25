#pragma once


#include "model/scene.h"
#include "model/cylinder.h"

#include <QObject>


namespace view {


class IViewer/*: public QObject*/ {
//    Q_OBJECT
public:
    virtual ~IViewer() = default;
//public slots:
    virtual void onSceneUpdated     (model::IScene::TPtr    const &scene)       = 0;
    virtual void onCylinderUpdated  (model::ICylinder::TPtr const &cylinder)    = 0;
};


} // view::gui
