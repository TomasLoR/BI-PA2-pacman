#include <algorithm>
#include <sstream>

#include "CScoreBoard.h"

const std::string FILENAME = "examples/Scoreboard.txt";

void CScoreBoard::update(unsigned int score) {
    clearConsole();
    m_currScore = score;
    if (!loadFile()) {
        std::cout << "Unable to update scoreboard" << std::endl;
        backToMenu();
        return;
    }
    m_players.emplace_back(m_currPlayer, m_currScore);
    std::sort(m_players.begin(), m_players.end(), compareScores);
    if (!writeFile()) {
        std::cout << "Unable to update scoreboard" << std::endl;
        backToMenu();
    }
}

void CScoreBoard::display() const {
    clearConsole();
    std::ifstream file;
    if (!openInFile(file)) {
        std::cout << "Error occurred while opening inFile: " << FILENAME << std::endl;
        std::cin.ignore();
        backToMenu();
        return;
    }
    std::cout << "            |Scoreboard|" << std::endl
              << "-----------------------------------" << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        if (!validScoreboard(line)) {
            file.close();
            std::cout << "Invalid scoreboard format at this line detected" << std::endl;
            std::cin.ignore();
            backToMenu();
            return;
        }
    }
    file.close();
    std::cin.ignore();
    backToMenu();
}

void CScoreBoard::receiveNickname() {
    clearConsole();
    std::cout << "Enter player nickname (no white spaces):" << std::endl;
    std::cin.ignore();
    inputNickname();

    if (!std::cin.eof()) {
        std::cout << "Your nickname will be: " << m_currPlayer << std::endl;
        backToMenu();
    }
}

void CScoreBoard::inputNickname() {
    while (!std::cin.eof()) {
        std::string line;
        std::string nick;
        getline(std::cin, line);
        std::istringstream iss(line);

        if (validNickname(iss, nick)) {
            m_currPlayer = nick;
            break;
        }
        std::cout << "Invalid nickname format, please try again:" << std::endl;
    }
}

bool CScoreBoard::validNickname(std::istringstream &iss, std:: string &nick) const {
    if (iss >> nick && iss.eof()) {
        return true;
    }
    return false;
}

bool CScoreBoard::loadFile() {
    std::ifstream inFile;
    if (!openInFile(inFile)) {
        std::cout << "Error occurred while opening inFile: " << FILENAME << std::endl;
        return false;
    }
    m_players.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (!validScoreboard(line)) {
            inFile.close();
            std::cout << "Invalid scoreboard format detected" << std::endl;
            return false;
        }
        std::istringstream iss(line);
        std::string name;
        unsigned int score;
        iss >> name >> score;
        m_players.emplace_back(name, score);
    }
    inFile.close();
    return true;
}

bool CScoreBoard::writeFile() const {
    std::ofstream outFile;
    if (!openOutFile(outFile)) {
        std::cout << "Error occurred while opening outFile: " << FILENAME << std::endl;
        return false;
    }
    for (const auto &player: m_players) {
        outFile << player.first << ' ' << player.second << std::endl;
    }
    outFile.close();
    return true;
}

bool CScoreBoard::openInFile(std::ifstream &inFile) const {
    inFile.open(FILENAME);
    if (!inFile) {
        return false;
    }
    return true;
}

bool CScoreBoard::openOutFile(std::ofstream &outFile) const {
    outFile.open(FILENAME);
    if (!outFile) {
        return false;
    }
    return true;
}

bool CScoreBoard::validScoreboard(const std::string &line) const {
    std::istringstream iss(line);
    std::string name;
    int score;
    if (iss >> name >> score) {
        return true;
    }
    return false;
}

void CScoreBoard::backToMenu() const {
    std::cout << "Press 'enter' to return to main menu..." << std::endl;
    std::cin.ignore();
}

void CScoreBoard::clearConsole() const {
    std::cout << "\033[2J\033[H";
}

bool CScoreBoard::compareScores(const std::pair<std::string, unsigned int> &p1,
                                const std::pair<std::string, unsigned int> &p2) {
    return p1.second > p2.second;
}