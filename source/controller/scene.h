#pragma once


#include <qsharedpointer.h>

#include "model/cylinder.h"


namespace controller {


class IScene {
public:
    typedef QSharedPointer<IScene> TPtr;
    virtual ~IScene() = default;
};


} // controller
