#include "CPacMan.h"

CPacMan::CPacMan(const CPosition &position) : m_startPosition(position), m_currPosition(position) {}

void CPacMan::print() const {
    std::cout << m_pacmanChar;
}

void CPacMan::printStats() const {
    std::cout << "LIVES: " << m_lives << std::endl
              << "SCORE: " << m_score << std::endl;
    if (m_canEat) {
        std::cout << "Remaining eating turns: " << m_eatingTurns + 1 << std::endl;
    } else {
        std::cout << "Can not eat ghosts" << std::endl;
    }
}

void CPacMan::move(const CPosition &newPosition) {
    m_currPosition = newPosition;
    m_teleported = false;
}

void CPacMan::respawn() {
    m_currPosition = m_startPosition;
}

void CPacMan::spawn(const CPosition &position) {
    m_startPosition = position;
    m_currPosition = position;
}

bool CPacMan::inSpawn() const {
    if (m_currPosition == m_startPosition) {
        return true;
    }
    return false;
}

void CPacMan::losingLifeNotification() const {
    cleanConsole();
    std::cout << "You have lost a life, but do not worry you still have: " << m_lives << " lives" << std::endl
              << "Press enter to respawn you and all the ghosts..." << std::endl;
    std::cin.ignore().ignore();;
}

void CPacMan::cleanConsole() const {
    std::cout << "\033[2J\033[H";
}