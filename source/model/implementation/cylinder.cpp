#include "cylinder.h"


static size_t DEFAULT_VERTICES_COUNT_LIMIT = 100;


namespace model::implementation {


void CCylinder::setVerticesNumber(size_t const &vertices_number) {
    if (vertices_number > DEFAULT_VERTICES_COUNT_LIMIT)
        m_vertices_number = DEFAULT_VERTICES_COUNT_LIMIT;
    else
        m_vertices_number = vertices_number;
}


void CCylinder::setColor(QColor const &color) {
    m_color = color;
}


size_t CCylinder::getVerticesNumber() const {
    return m_vertices_number;
}


QColor CCylinder::getColor() const {
    return m_color;
}


} // model::implementation
