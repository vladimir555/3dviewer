#pragma once


#include "object.h"


namespace model {


class ICylinder: public IObject {
public:
    typedef QSharedPointer<ICylinder> TPtr;
    virtual ~ICylinder() = default;
    virtual size_t getVerticesNumber() const = 0;
};


} // model
