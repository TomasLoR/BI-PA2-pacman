#include <fstream>
#include <sstream>

#include "CDifficulty.h"

void CDifficulty::initialize() {
    displayDifficulty();
    if (handleDifficulty(std::cin)) {
        informUser();
    }
    backToMenu();
}

void CDifficulty::displayDifficulty() const {
    clearConsole();
    std::cout << "                          |Difficulty|" << std::endl
              << "--------------------------------------------------------------" << std::endl
              << "[\"EASY\"]" << std::endl
              << "[\"MEDIUM\"]" << std::endl
              << "[\"HARD\"]" << std::endl;
}

bool CDifficulty::handleDifficulty(std::istream &input) {
    std::string difficulty;
    input >> difficulty;
    std::string filename = createFilename(difficulty);
    if (std::cin.eof() || !loadFile(filename)) {
        return false;
    }
    return true;
}

std::string CDifficulty::createFilename(const std::string &difficulty) const {
    std::string filename = "examples/difficulties/" + difficulty + ".txt";
    return filename;
}

bool CDifficulty::loadFile(const std::string &filename) {
    std::ifstream inFile;
    if (!openInFile(inFile, filename)) {
        std::cout << "Error occurred while opening inFile: " << filename << std::endl;
        return false;
    }
    std::string line;
    if (std::getline(inFile, line)) {
        if (!trySaveParameters(line)) {
            inFile.close();
            std::cout << "Invalid difficulty file format detected" << std::endl;
            return false;
        }
        inFile.close();
        return true;
    } else {
        inFile.close();
        std::cout << "Difficulty file is empty" << std::endl;
        return false;
    }
}

bool CDifficulty::openInFile(std::ifstream &inFile, const std::string &filename) const {
    inFile.open(filename);
    if (!inFile) {
        return false;
    }
    return true;
}

bool CDifficulty::trySaveParameters(const std::string &line) {
    std::istringstream iss(line);
    char pipe;
    if (!(iss >> m_dumbSpeed >> m_smartSpeed >> m_patternSpeed >> m_frightSpeed >> pipe >> m_eatingLen >> m_lives)) {
        return false;
    }
    if (!iss.eof() || m_dumbSpeed == 0 || m_smartSpeed == 0 || m_patternSpeed == 0 || m_frightSpeed >= 0
        || m_eatingLen <= 0 || m_lives <= 0) {
        return false;
    }
    return true;
}

void CDifficulty::informUser() const {
    clearConsole();
    std::cout << "Info about the difficulty you chose:" << std::endl
              << "Dumb ghosts speed: " << m_dumbSpeed << std::endl
              << "Smart ghost speed: " << m_smartSpeed << std::endl
              << "Pattern ghost speed: " << m_patternSpeed << std::endl
              << "Frightened mode speed: " << m_frightSpeed << std::endl
              << "Cherry bonus will last: " << m_eatingLen << " turns" << std::endl
              << "Pacman will have: " << m_lives << " lives" << std::endl;
}

void CDifficulty::backToMenu() const {
    std::cout << "Press 'enter' to return to main menu..." << std::endl;
    std::cin.ignore().ignore();
}

void CDifficulty::clearConsole() const {
    std::cout << "\033[2J\033[H";
}

int CDifficulty::getDumbSpeed() const {
    return m_dumbSpeed;
}

int CDifficulty::getSmartSpeed() const {
    return m_smartSpeed;
}

int CDifficulty::getPatternSpeed() const {
    return m_patternSpeed;
}

int CDifficulty::getEatingLen() const {
    return m_eatingLen;
}

int CDifficulty::getFrightSpeed() const {
    return m_frightSpeed;
}

int CDifficulty::getLives() const {
    return m_lives;
}
