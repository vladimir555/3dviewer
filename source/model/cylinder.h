#pragma once


#include "object.h"


namespace model {


class ICylinder: public IObject {
public:
    static int      const DEFAULT_VERTICES_NUMBER        = 5;
    static int      const DEFAULT_VERTICES_NUMBER_MIN    = 3;
    static int      const DEFAULT_VERTICES_NUMBER_MAX    = 50;
    static QColor   const DEFAULT_COLOR;

    typedef QSharedPointer<ICylinder> TPtr;
    virtual ~ICylinder() = default;
    virtual int getVerticesNumber() const = 0;
};


} // model
