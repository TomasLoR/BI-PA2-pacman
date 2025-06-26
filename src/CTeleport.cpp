#include "CTeleport.h"

CTeleport::CTeleport(const CPosition &position, const CPosition &positionToTp, char charTile) :
        CTile(position, charTile), m_positionToTp(positionToTp) {}

void CTeleport::print() const {
    std::cout << m_tileChar;
}

bool CTeleport::canStepOn() const {
    return true;
}

void CTeleport::doEffect(CPacMan &pacman) const {
    pacman.m_currPosition = m_positionToTp;
    pacman.m_teleported = true;
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You have been teleported!" << std::endl;
}