#pragma once


#include "object.h"


namespace model {


class ICylinder: public IObject {
public:
    typedef QSharedPointer<ICylinder> TPtr;
    virtual ~ICylinder() = default;
    virtual void setVerticesNumber(size_t const &count) = 0;
};


} // model
