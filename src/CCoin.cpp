#include "CCoin.h"

CCoin::CCoin(const CPosition &position, char charTile) : CTile(position, charTile) {}

void CCoin::print() const {
    std::cout << m_tileChar;
}

bool CCoin::canStepOn() const {
    return true;
}

void CCoin::doEffect(CPacMan &pacman) const {
    pacman.m_score += m_score;
    pacman.m_collectedCoins++;
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You have collected a coin!" << std::endl;
}
