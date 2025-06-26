#include "CPacmanSpawn.h"

CPacmanSpawn::CPacmanSpawn(const CPosition &position, char charTile) : CTile(position, charTile) {}

void CPacmanSpawn::print() const {
    std::cout << m_tileChar;
}

bool CPacmanSpawn::canStepOn() const {
    return true;
}

void CPacmanSpawn::doEffect(CPacMan &pacman) const {
    if (pacman.m_canEat) {
        pacman.m_score += m_score;
    }
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You have stepped on your spawnpoint!" << std::endl;
}
