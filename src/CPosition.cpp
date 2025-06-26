#include "CPosition.h"

CPosition::CPosition(unsigned int row, unsigned int column) : m_row(row), m_column(column) {}

bool CPosition::operator==(const CPosition &other) const {
    return (m_row == other.m_row) && (m_column == other.m_column);
}

bool CPosition::operator!=(const CPosition &other) const {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const CPosition &position) {
    os << '[' << position.m_row << ", " << position.m_column << ']';
    return os;
}

bool CPosition::operator<(const CPosition &other) const {
    if (m_row < other.m_row) {
        return true;
    } else if (m_row > other.m_row) {
        return false;
    } else {
        return m_column < other.m_column;
    }
}

CPosition &CPosition::operator+=(const CPosition &other) {
    m_row += other.m_row;
    m_column += other.m_column;
    return *this;
}

const CPosition &CPosition::up() {
    m_row--;
    return *this;
}

const CPosition &CPosition::down() {
    m_row++;
    return *this;
}

const CPosition &CPosition::left() {
    m_column--;
    return *this;
}

const CPosition &CPosition::right() {
    m_column++;
    return *this;
}