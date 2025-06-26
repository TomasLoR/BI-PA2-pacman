#include "CMenu.h"


bool CMenu::initialize() {
    displayChoice();
    while (handleChoice(std::cin)) {
        displayChoice();
    }
    if (m_choice == "Quit" || std::cin.eof()) {
        return false;
    }
    return true;
}

void CMenu::displayChoice() const {
    clearConsole();
    std::cout << "            |Main menu|" << std::endl
              << "-----------------------------------" << std::endl
              << "[\"Play\"] start playing" << std::endl
              << "[\"Difficulty\"] enter difficulty menu" << std::endl
              << "[\"Scoreboard\"] show scoreboard" << std::endl
              << "[\"Nickname\"] enter your nickname" << std::endl
              << "[\"Quit\"] stop this application" << std::endl;
}

bool CMenu::handleChoice(std::istream &input) {
    input >> m_choice;
    while (!validChoice()) {
        if (std::cin.eof()) {
            return false;
        }
        std::cout << "Invalid choice. Please try again." << std::endl;
        input >> m_choice;
    }
    return reactToChoice();
}

bool CMenu::validChoice() const {
    if (m_choice == "Play" || m_choice == "Difficulty" || m_choice == "Scoreboard" || m_choice == "Nickname" ||
        m_choice == "Quit") {
        return true;
    }
    return false;
}

bool CMenu::reactToChoice() {
    if (m_choice == "Difficulty") {
        m_difficulty.initialize();
        if (!std::cin.eof()) {
            return true;
        }
    } else if (m_choice == "Scoreboard") {
        m_scoreBoard.display();
        if (!std::cin.eof()) {
            return true;
        }
    } else if (m_choice == "Nickname") {
        m_scoreBoard.receiveNickname();
        if (!std::cin.eof()) {
            return true;
        }
    }
    return false;
}

void CMenu::updateScoreboard(unsigned int score) {
    m_scoreBoard.update(score);
}

const CDifficulty &CMenu::getDifficulty() const {
    return m_difficulty;
}

void CMenu::clearConsole() const {
    std::cout << "\033[2J\033[H";
}