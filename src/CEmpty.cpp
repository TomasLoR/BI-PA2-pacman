#include "CEmpty.h"

CEmpty::CEmpty(const CPosition &position, char charTile) : CTile(position, charTile) {}

void CEmpty::print() const {
    std::cout << m_tileChar;
}

bool CEmpty::canStepOn() const {
    return true;
}

void CEmpty::doEffect(CPacMan &pacman) const {
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You have stepped on an empty tile!" << std::endl;
}