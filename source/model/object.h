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
    virtual void setColor(QColor const &color) = 0;
};


} // model
