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
    CCylinder();
    virtual ~CCylinder() = default;

    void setVerticesNumber(int const &count);
    void setColor(QColor const &color);

    int     getVerticesNumber() const override;
    QColor  getColor()          const override;

private:
    int     m_vertices_number;
    QColor  m_color;
};


} // model::implementation
