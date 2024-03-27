#include "cylinder.h"


namespace model::implementation {


CCylinder::CCylinder()
:
    m_vertices_number   (DEFAULT_VERTICES_NUMBER),
    m_color             (DEFAULT_COLOR)
{}


void CCylinder::setVerticesNumber(int const &vertices_number) {
    if   (vertices_number > DEFAULT_VERTICES_NUMBER_MAX)
        m_vertices_number = DEFAULT_VERTICES_NUMBER_MAX;
    else
        m_vertices_number = vertices_number;
}


void CCylinder::setColor(QColor const &color) {
    m_color = color;
}


int CCylinder::getVerticesNumber() const {
    return m_vertices_number;
}


QColor CCylinder::getColor() const {
    return m_color;
}


} // model::implementation
