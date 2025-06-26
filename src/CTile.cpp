#include "CTile.h"

CTile::CTile(const CPosition &position, char charTile) : m_position(position), m_tileChar(charTile) {}

const CPosition &CTile::getPosition() const {
    return m_position;
}