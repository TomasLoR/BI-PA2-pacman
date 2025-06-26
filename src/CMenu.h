#pragma once

#include "CDifficulty.h"
#include "CScoreBoard.h"

/**
 * Class representing menu of the application.
 */
class CMenu {
public:
    CMenu() = default;

    CMenu(const CMenu &) = delete;

    CMenu &operator=(const CMenu &) = delete;

    ~CMenu() = default;

    /**
     * Method that initializes main menu and manages it.
     * @returns false if if "Quit" option was chosen or EOF was detected, true if "Play" option was chosen
     */
    bool initialize();

    /**
     * Method that calls for update on m_scoreboard.
     * @param score
     */
    void updateScoreboard(unsigned int score);

    /**
     * Getter method allows accessing the chosen difficulty.
     * @returns reference to chosen difficulty
     */
    const CDifficulty &getDifficulty() const;

private:
    /**
     * Method that prints out the main menu.
     */
    void displayChoice() const;

    /**
     * Method that handles users input in main menu.
     * @param input
     * @returns the returning value of reactToChoice method
     */
    bool handleChoice(std::istream &input);

    /**
     * Method that checks if the user's input is valid.
     * @returns if the choice is valid, false otherwise
     */
    bool validChoice() const;

    /**
     * Method that reacts to chosen menu option, calling methods on m_difficulty or m_scoreboard if needed.
     * @returns false if "Play" or "Quit" was chosen, true otherwise
     */
    bool reactToChoice();

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void clearConsole() const;

    CDifficulty m_difficulty;
    CScoreBoard m_scoreBoard;
    std::string m_choice;
};