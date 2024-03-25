#pragma once


#include <QColor>
#include <qsharedpointer.h>


namespace model {


//enum class TObjectType {
//    UNKNOWN,
//    CYLINDER
//};


class IObject {
public:
    typedef QSharedPointer<IObject> TPtr;
    virtual ~IObject() = default;
    virtual QColor getColor() const = 0;
};


} // model
