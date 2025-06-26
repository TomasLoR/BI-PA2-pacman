#include "CGhostSpawn.h"

CGhostSpawn::CGhostSpawn(const CPosition &position, char charTile) : CTile(position, charTile) {}

void CGhostSpawn::print() const {
    std::cout << m_tileChar;
}

bool CGhostSpawn::canStepOn() const {
    return true;
}

void CGhostSpawn::doEffect(CPacMan &pacman) const {
    pacman.m_score += m_score;
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You have collected a ghost spawnpoint, +50 score (this ghost spawnpoint is now invisible)"
              << std::endl;
}