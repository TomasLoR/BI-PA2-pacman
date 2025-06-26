#include "CPatternGhost.h"

CPatternGhost::CPatternGhost(const CPosition &position, int speed, int frightSpeed, char ghostChar) :
        CGhost(position, speed, frightSpeed, ghostChar) {}

void CPatternGhost::print() const {
    if (!m_frightened) {
        std::cout << m_ghostChar;
    } else {
        std::cout << m_frightChar;
    }
}

void CPatternGhost::move(const CMap &map, const CPosition &pacmanPos) {
    updateSpeedCnt();
    while (m_currSpeed >= 0) {

        if (!m_frightened) {
            if (!isCollision(pacmanPos)) {

                if (!isPacmanNearby(pacmanPos, map)) {
                    for (int i = 0; i < 4; i++) {
                        CPosition newPos = m_currPosition;
                        if (map.newPosIfPossible(newPos, i)) {
                            m_currPosition = newPos;
                            break;
                        }
                    }
                } else {
                    m_currPosition = pacmanPos;
                }
            }
        } else {
            frightenedMovement(map, pacmanPos);
        }

        if (m_currSpeed == 0) {
            resetSpeedCnt();
            break;
        }
        updateSpeedCnt();
    }
}

bool CPatternGhost::isPacmanNearby(const CPosition &pacmanPos, const CMap &map) const {
    for (int i = 0; i < 4; i++) {
        CPosition newPos = m_currPosition;
        if (map.newPosIfPossible(newPos, i) && newPos == pacmanPos) {
            return true;
        }
    }
    return false;
}