#pragma once


#include <qsharedpointer.h>

#include "model/object.h"


namespace controller {


class IViewer {
public:
    typedef QSharedPointer<IViewer> TPtr;
    virtual ~IViewer() = default;

//    virtual void selectObjectType(model::TObjectType const &object_type) = 0;
};


} // controller
