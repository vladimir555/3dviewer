#pragma once


#include "model/scene.h"


namespace model::implementation {


class CScene: public IScene {
public:
    typedef QSharedPointer<CScene> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }
    CScene() = default;
    virtual ~CScene() = default;

    void setRotationAxys(TRotationAxis const &rotation_axis);
    TRotationAxis getRotationAxys() const override;

private:
    TRotationAxis m_rotation_axis;
};


} // model::implementation
