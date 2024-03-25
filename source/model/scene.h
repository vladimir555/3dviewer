#pragma once


#include "object.h"


namespace model {


class IScene {
public:
    typedef QSharedPointer<IScene> TPtr;
    virtual ~IScene() = default;

    enum class TRotationAxis {
        UNKNOWN,
        X, Y, Z
    };
    
    virtual TRotationAxis getRotationAxys() const = 0;
};


} // model
