#include <queue>
#include <set>
#include <map>

#include "CSmartGhost.h"

CSmartGhost::CSmartGhost(const CPosition &position, int speed, int frightSpeed, char ghostChar) : CGhost(position,
                                                                                                         speed,
                                                                                                         frightSpeed,
                                                                                                         ghostChar) {}

void CSmartGhost::print() const {
    if (!m_frightened) {
        std::cout << m_ghostChar;
    } else {
        std::cout << m_frightChar;
    }
}

void CSmartGhost::move(const CMap &map, const CPosition &pacmanPos) {
    updateSpeedCnt();
    while (m_currSpeed >= 0) {

        if (!m_frightened) {
            if (!isCollision(pacmanPos)) {
                std::map<CPosition, CPosition> childParent;
                bool found = false;

                bfsSearch(map, pacmanPos, childParent, found);

                if (found) {
                    CPosition move = findMove(childParent, pacmanPos);
                    m_currPosition = move;
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


void CSmartGhost::bfsSearch(const CMap &map, const CPosition &pacmanPos,
                            std::map<CPosition, CPosition> &childParent, bool &found) const {
    std::set<CPosition> visitedPos;
    std::queue<CPosition> queuePos;
    queuePos.push(m_currPosition);
    visitedPos.insert(m_currPosition);

    while (!queuePos.empty()) {
        CPosition currPos = queuePos.front();

        if (currPos == pacmanPos) {
            found = true;
            break;
        }
        queuePos.pop();

        for (int i = 0; i < 4; i++) {
            CPosition nextPos = currPos;
            map.newPosIfPossible(nextPos, i);

            if (visitedPos.insert(nextPos).second) {
                queuePos.push(nextPos);
                childParent[nextPos] = currPos;
            }
        }
    }
}

CPosition CSmartGhost::findMove(const std::map<CPosition, CPosition> &childParent, const CPosition &pacmanPos) {
    std::vector<CPosition> path = findPath(childParent, pacmanPos);
    return path[path.size() - 2];
}

std::vector<CPosition> CSmartGhost::findPath(const std::map<CPosition, CPosition> &childParent,
                                             const CPosition &pacmanPos) {
    std::vector<CPosition> path;
    path.emplace_back(pacmanPos);
    CPosition current = pacmanPos;

    while (current != m_currPosition) {
        current = childParent.find(current)->second;
        path.emplace_back(current);
    }
    return path;
}