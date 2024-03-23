#pragma once


#include "object.h"


namespace model {


class ICylinder: public IObject {
public:
    virtual void setVerticesNumber(uint64_t const &count) = 0;
};



} // model
