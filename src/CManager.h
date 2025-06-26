#pragma once

#include "CMenu.h"
#include "CGame.h"

/**
 * Class representing manager of the application connecting menu, difficulty and game.
 */
class CManager {
public:
    CManager() = default;

    CManager(const CManager &) = delete;

    CManager &operator=(const CManager &) = delete;

    ~CManager() = default;

    /**
     * Method that starts the application and keeps it running until aplication-end criteria are met.
     * @returns 0 if aplication ended sucessfully, 1 otherwise
     */
    int run();

private:
    /**
     * Method that prints out summary of gaming session based on given score.
     * @param gameScore
     */
    void sessionSummary(int &gameScore) const;

    /**
     * Method that prints out message before closing aplication.
     */
    void closingAppNotification() const;

    /**
     * Method that prompts user to press 'enter' to return to main menu.
     */
    void backToMenu() const;

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void clearConsole() const;

    CMenu m_menu;
};