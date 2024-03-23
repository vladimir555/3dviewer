#pragma once


#include <QColor>


namespace model {


enum class TObjectType {
    UNKNOWN,
    CYLINDER
}; // TModelType


class IObject {
public:
    virtual void setColor(QColor const &color) = 0;
};


} // model
