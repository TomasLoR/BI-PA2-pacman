#include "CManager.h"


int CManager::run() {
    while (true) {
        if (m_menu.initialize()) {
            std::cout << "Starting game..." << std::endl;
            CGame game(m_menu.getDifficulty());
            int score = game.start();
            if (std::cin.eof()) {
                closingAppNotification();
                return 0;
            }

            sessionSummary(score);
            m_menu.updateScoreboard(score);
        } else {
            closingAppNotification();
            return 0;
        }
    }
}

void CManager::sessionSummary(int &gameScore) const {
    clearConsole();
    if (gameScore > 0) {
        std::cout << "GAME OVER, you collected all the coins!" << std::endl
                  << "Your score is: |" << gameScore << '|' << std::endl << std::endl;
    } else {
        gameScore *= -1;
        std::cout << "GAME OVER, you have 0 lives" << std::endl
                  << "Your score is: *" << gameScore << '*' << std::endl << std::endl;
    }
    backToMenu();
}

void CManager::closingAppNotification() const {
    if (std::cin.eof()) {
        std::cout << "EOF detected" << std::endl;
    }
    std::cout << "Closing aplication..." << std::endl;
}

void CManager::backToMenu() const {
    std::cout << "Press enter to return back to main menu..." << std::endl;
    std::cin.ignore().ignore();
}

void CManager::clearConsole() const {
    std::cout << "\033[2J\033[H";
}