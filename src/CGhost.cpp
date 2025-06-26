#include <algorithm>

#include "CGhost.h"

CGhost::CGhost(const CPosition &position, int startSpeed, int frightStartSpeed, char ghostChar) : m_startSpeed(
        startSpeed), m_startPosition(position), m_frightStartSpeed(frightStartSpeed), m_ghostChar(ghostChar) {

    m_currSpeed = m_startSpeed;
    m_frightCurrSpeed = m_frightStartSpeed;
    m_currPosition = m_startPosition;
}

void CGhost::respawn() {
    m_currPosition = m_startPosition;
}

void CGhost::updateSpeedCnt() {
    if (m_currSpeed > 0) {
        m_currSpeed--;
    } else if (m_currSpeed < 0) {
        m_currSpeed++;
    }
}

const CPosition &CGhost::getCurrPos() const {
    return m_currPosition;
}

bool CGhost::isCollision(const CPosition &pacmanPos) const {
    if (pacmanPos == m_currPosition) {
        return true;
    }
    return false;
}

void CGhost::resetSpeedCnt() {
    m_currSpeed = m_startSpeed;
}

void CGhost::toggleFrightened() {
    m_frightened = !m_frightened;
    m_frightCurrSpeed = m_frightStartSpeed;
}

void CGhost::frightenedMovement(const CMap &map, const CPosition &pacmanPos) {
    m_frightCurrSpeed++;
    if (m_frightCurrSpeed == 0) {
        std::vector<std::pair<CPosition, unsigned int>> moves;
        prepMoves(map, pacmanPos, moves);
        if (!moves.empty()) {
            std::sort(moves.begin(), moves.end(), compareMoves);
            m_currPosition = moves[0].first;
        }

        m_frightCurrSpeed = m_frightStartSpeed;
    }
}

unsigned int CGhost::ghostPacmanDistance(const CPosition &ghostPos, const CPosition &pacmanPos) const {
    unsigned int distanceRow = (pacmanPos.m_row > ghostPos.m_row) ? pacmanPos.m_row - ghostPos.m_row : ghostPos.m_row -
                                                                                                       pacmanPos.m_row;
    unsigned int distanceCol = (pacmanPos.m_column > ghostPos.m_column) ? pacmanPos.m_column - ghostPos.m_column :
                               ghostPos.m_column - pacmanPos.m_column;
    return distanceRow + distanceCol;
}

void
CGhost::prepMoves(const CMap &map, const CPosition &pacmanPos, std::vector<std::pair<CPosition, unsigned int>> &moves) {
    unsigned int distance = ghostPacmanDistance(m_currPosition, pacmanPos);
    for (int i = 0; i < 4; i++) {
        CPosition newPos = m_currPosition;
        if (map.newPosIfPossible(newPos, i)) {
            unsigned int newDistance = ghostPacmanDistance(newPos, pacmanPos);
            if (newDistance > distance) {
                moves.emplace_back(newPos, newDistance);
            }
        }
    }
}

bool CGhost::compareMoves(const std::pair<CPosition, unsigned int> &m1,
                                 const std::pair<CPosition, unsigned int> &m2)
{
    return m1.second > m2.second;
}
