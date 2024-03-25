#pragma once


#include "object.h"


namespace model {


class ICylinder: public IObject {
public:
    typedef QSharedPointer<ICylinder> TPtr;
    virtual ~ICylinder() = default;
    virtual void setVerticesNumber(size_t const &count) = 0;
};


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
