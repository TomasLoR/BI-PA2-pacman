#pragma once

#include <iostream>
#include <fstream>
#include <vector>

/**
 * Class representing scoreboard of best players.
 */
class CScoreBoard {
public:
    CScoreBoard() = default;

    ~CScoreBoard() = default;

    /**
     * Method that updates scoreboard based on given score.
     * @param score
     */
    void update(unsigned int score);

    /**
     * Method that prints out current the scoreboard.
     */
    void display() const;

    /**
     * Method that prompts user to enter his player nickname.
     */
    void receiveNickname();

private:
    /**
     * Method that tries to load data from the scoreboard file.
     * @returns true if it load successfully, false otherwise
     */
    bool loadFile();

    /**
     * Method that tries to write new/updated data to the scoreboard file.
     * @returns true if the writes succuessfully, false otherwise
     */
    bool writeFile() const;

    /**
     * Method that tries to open the input file.
     * @param file
     * @returns true if the file is opened without any errors, false otherwise
     */
    bool openInFile(std::ifstream &file) const;

    /**
     * Method that tries to open the output file.
     * @param file
     * @returns true if the file is opened without any errors, false otherwise
     */
    bool openOutFile(std::ofstream &file) const;

    /**
     * Method that validates the format of the string line in scoreboard.
     * @param line
     * @returns true if the line has desired format, false otherwise
     */
    bool validScoreboard(const std::string &line) const;

    /**
     * Method that manages users input of the nicname.
     */
    void inputNickname();

    /**
     * Method that validates nick's format
     * @param iss
     * @param nick
     * @returns true if the format is valid, false otherwise
     */
    bool validNickname(std::istringstream &iss, std:: string &nick) const;

    /**
     * Method that prompts user to press 'enter' to return to main menu.
     */
    void backToMenu() const;

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void clearConsole() const;

    /**
     * Method used as comparator function for sorting scores in descending order.
     * @param p1
     * @param p2
     * @returns true if p1's score is greater than p2's score, false otherwise.
     */
    static bool compareScores(const std::pair<std::string, unsigned int> &p1, const std::pair<std::string,
                              unsigned int> &p2);

    std::vector<std::pair<std::string, unsigned int>> m_players;
    std::string m_currPlayer = "unknown";
    unsigned int m_currScore{};
};