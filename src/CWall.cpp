#include "CWall.h"

CWall::CWall(const CPosition &position, char charTile) : CTile(position, charTile) {}

void CWall::print() const {
    std::cout << m_tileChar;
}

bool CWall::canStepOn() const {
    return false;
}

void CWall::doEffect(CPacMan &pacman) const {
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You are standing on a wall, congratulations you achieved the impossible!" << std::endl;
}