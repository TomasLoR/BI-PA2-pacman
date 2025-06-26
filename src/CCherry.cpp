#include "CCherry.h"

CCherry::CCherry(const CPosition &position, int bonusLen, char charTile) : CTile(position, charTile),
                                                                           m_bonusLen(bonusLen) {}

void CCherry::print() const {
    std::cout << m_tileChar;
}

bool CCherry::canStepOn() const {
    return true;
}

void CCherry::doEffect(CPacMan &pacman) const {
    pacman.m_eatingTurns += m_bonusLen;
    pacman.m_canEat = true;
    pacman.m_score += m_score;
    std::cout << "Your position is: " << pacman.m_currPosition << std::endl
              << "You have collected a cherry, now you can chase ghosts for " << m_bonusLen << " more turns!"
              << std::endl;
}