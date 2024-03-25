#include "scene.h"


namespace model::implementation {


CScene::CScene()
:
    m_rotation_axis(TRotationAxis::X)
{}


void CScene::setRotationAxys(TRotationAxis const &rotation_axis) {
    m_rotation_axis = rotation_axis;
}


CScene::TRotationAxis CScene::getRotationAxys() const {
    return m_rotation_axis;
}


} // model::implementation
