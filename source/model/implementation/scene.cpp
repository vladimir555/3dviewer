#include "scene.h"


namespace model::implementation {


void CScene::setRotationAxys(TRotationAxis const &rotation_axis) {
    m_rotation_axis = rotation_axis;
}


CScene::TRotationAxis CScene::getRotationAxys() const {
    return m_rotation_axis;
}


} // model::implementation
