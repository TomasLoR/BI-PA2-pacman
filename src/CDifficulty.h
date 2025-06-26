#pragma once

#include <string>
#include <iostream>

class CDifficulty {
public:
    CDifficulty() = default;

    CDifficulty(const CDifficulty &) = default;

    CDifficulty &operator=(const CDifficulty &) = default;

    ~CDifficulty() = default;

    /**
     * Method that difficulty menu manages it.
     */
    void initialize();

    /**
     * Getter method that allows accessing the speed of the dumb ghost.
     * @returns speed of the dumb ghost
     */
    int getDumbSpeed() const;

    /**
     * Getter method that allows accessing the speed of the smart ghost.
     * @returns speed of the smart ghost
     */
    int getSmartSpeed() const;

    /**
     * Getter method that allows accessing the speed of the pattern ghost.
     * @returns speed of the pattern ghost
     */
    int getPatternSpeed() const;


    /**
     * Getter method that allows accessing the number of turns eating mode will last.
     * @returns number of turns eating mode will last
     */
    int getEatingLen() const;

    /**
     * Getter method that allows accessing the speed in frightened mode.
     * @returns speed in frightened mode
     */
    int getFrightSpeed() const;

    /**
     * Getter method that allows accessing the number of lives of Pacman.
     * @return the number of lives of Pacman
     */
    int getLives() const;

private:
    /**
     * Method that prints out the difficulty menu.
     */
    void displayDifficulty() const;

    /**
     * Method that handles users input in difficulty menu.
     * @param input
     * @return
     */
    bool handleDifficulty(std::istream& input);

    /**
     * Method that converts users chosen difficulty into filename.
     * @param difficulty
     * @returns created filename
     */
    std::string createFilename(const std::string &difficulty) const;

    /**
     * Method that tries to load data from the config file.
     * @param filename
     * @returns true if it loads successfully, false otherwise
     */
    bool loadFile(const std::string &filename);

    /**
     * Method that tries to open input file with given filename.
     * @param inFile
     * @param filename
     * @returns true if the file is opened without any errors, false otherwise
     */
    bool openInFile(std::ifstream &inFile, const std::string &filename) const;

    /**
     * Method that tries to save parameters into member variables.
     * @param line
     * @returns true if saving is successfull, false otherwise
     */
    bool trySaveParameters(const std::string& line);

    /**
     * Method that informs user about specifics of the chosen difficulty.
     */
    void informUser() const;

    /**
     * Method that prompts user to press 'enter' to return to main menu.
     */
    void backToMenu() const;

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void clearConsole() const;

    int m_dumbSpeed = 1;
    int m_smartSpeed = 1;
    int m_patternSpeed = 1;
    int m_frightSpeed = -2;
    int m_eatingLen = 10;
    int m_lives = 3;
};