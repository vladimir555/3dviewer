#pragma once


#include "model/cylinder.h"


namespace model::implementation {


class CCylinder: public ICylinder {
public:
    typedef QSharedPointer<CCylinder> TPtr;
    template<typename ... TArgs>
    static TPtr create(TArgs ... args) {
        return TPtr::create(args ...);
    }
    CCylinder() = default;
    virtual ~CCylinder() = default;

    void setVerticesNumber(size_t const &count);
    void setColor(QColor const &color);

    size_t getVerticesNumber() const override;
    QColor getColor()          const override;

private:
    size_t m_vertices_number = 0;
    QColor m_color;
};


} // model::implementation
