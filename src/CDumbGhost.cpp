#include "CDumbGhost.h"

CDumbGhost::CDumbGhost(const CPosition &position, int speed, int frightSpeed, char ghostChar) : CGhost(position, speed,
                                                                                                       frightSpeed,
                                                                                                       ghostChar) {}

void CDumbGhost::print() const {
    if (!m_frightened) {
        std::cout << m_ghostChar;
    } else {
        std::cout << m_frightChar;
    }

}

void CDumbGhost::move(const CMap &map, const CPosition &pacmanPos) {
    updateSpeedCnt();
    while (m_currSpeed >= 0) {

        if (!m_frightened) {
            if (!isCollision(pacmanPos)) {
                int randNum = rand() % 4;
                int maxAttempts = 4;
                while (maxAttempts > 0) {
                    CPosition newPos = m_currPosition;
                    if (map.newPosIfPossible(newPos, randNum)) {
                        m_currPosition = newPos;
                        break;
                    }
                    randNum = (randNum + 1) % 4;
                    maxAttempts--;
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