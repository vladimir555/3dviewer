#include "cylinder.h"


static size_t DEFAULT_VERTICES_COUNT_LIMIT = 100;


namespace model::implementation {


void CCylinder::setVerticesNumber(size_t const &number) {
    if (number > DEFAULT_VERTICES_COUNT_LIMIT)
        m_vertices_number = DEFAULT_VERTICES_COUNT_LIMIT;
    else
        m_vertices_number = number;
}


void CCylinder::setColor(QColor const &color) {
    m_color = color;
}


} // model::implementation
