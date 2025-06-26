#include <fstream>
#include <sstream>

#include "CMap.h"

const int MINIMUM_ROWS = 10;
const int MINIMUM_COLUMNS = 10;

void CMap::create(const CDifficulty &difficulty) {
    m_difficulty = difficulty;
    while (true) {
        std::string mapName = receiveMapName(std::cin);
        nameToFilename(mapName);
        if (std::cin.eof()) {
            return;
        }
        if (loadFile(mapName)) {
            break;
        }
        backToMapSelection();
    }
    charsToTiles();
}

std::string CMap::receiveMapName(std::istream &input) const {
    clearConsole();
    std::cout << "Enter name of the chosen map (Simple, Normal, Advanced):" << std::endl;
    std::string mapName;
    input >> mapName;
    return mapName;
}

void CMap::nameToFilename(std::string &mapName) const {
    mapName = "examples/maps/" + mapName + ".txt";
}

bool CMap::loadFile(const std::string &filename) {
    std::ifstream inFile;
    if (!openInFile(inFile, filename)) {
        std::cout << "Error occurred while opening inFile: " << filename << std::endl;
        return false;
    }
    if (!loadParameters(inFile)) {
        inFile.close();
        std::cout << "Invalid parameters detected" << std::endl;
        return false;
    }
    if (!loadMap(inFile)) {
        std::cout << "Invalid map detected" << std::endl;
        inFile.close();
        resetData();
        return false;
    }
    return true;
}

bool CMap::openInFile(std::ifstream &inFile, const std::string &filename) const {
    inFile.open(filename);
    if (!inFile) {
        return false;
    }
    return true;
}

bool CMap::loadParameters(std::ifstream &inFile) {
    std::string line;
    if (getline(inFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> m_rowMax >> m_columnMax) || m_rowMax < MINIMUM_ROWS || m_columnMax < MINIMUM_COLUMNS) {
            std::cout << "Required parameters: min rows: " << MINIMUM_ROWS << ", min columns: " << MINIMUM_COLUMNS
                      << std::endl;
            return false;
        }
    } else {
        std::cout << "Map file is empty" << std::endl;
        return false;
    }
    return true;
}

bool CMap::loadMap(std::ifstream &inFile) {
    std::string line;
    unsigned int rowNum = 0;
    int pacmanCnt = 0;
    while (std::getline(inFile, line)) {
        if (line.length() - 1 != m_columnMax) {
            std::cout << "Invalid number of columns in the map" << std::endl;
            return false;
        }
        std::vector<char> row;
        for (size_t columnNum = 0; columnNum < line.length() - 1; columnNum++) {
            if (line[columnNum] == '.') {
                row.emplace_back('.');
                m_coinsCnt++;
            } else if (line[columnNum] == '@') {
                row.emplace_back('@');
            } else if (line[columnNum] == '#') {
                row.emplace_back('#');
            } else if (line[columnNum] == 'T') {
                row.emplace_back('T');
                m_teleportPositions.emplace_back(CPosition(rowNum, columnNum));
            } else if (line[columnNum] == ' ') {
                row.emplace_back(' ');
            } else if (line[columnNum] == 'p') {
                row.emplace_back('p');
                m_pacmanSpawnpoint = CPosition(rowNum, columnNum);
                pacmanCnt++;
            } else if (line[columnNum] == 'D') {
                row.emplace_back('g');
                m_ghosts.emplace_back(CPosition(rowNum, columnNum), 'D');
            } else if (line[columnNum] == 'S') {
                row.emplace_back('g');
                m_ghosts.emplace_back(CPosition(rowNum, columnNum), 'S');
            } else if (line[columnNum] == 'R') {
                row.emplace_back('g');
                m_ghosts.emplace_back(CPosition(rowNum, columnNum), 'R');
            } else {
                std::cout << "Invalid map symbol detected" << std::endl;
                return false;
            }
        }
        m_chars.emplace_back(row);
        rowNum++;
    }
    if (rowNum != m_rowMax) {
        std::cout << "Invalid number of rows in the map" << std::endl;
        return false;
    }
    if (!validateTileCount(pacmanCnt)) {
        std::cout << "Zero coins or invalid number of pacman spawnpoints detected" << std::endl;
        return false;
    }
    return true;
}

bool CMap::validateTileCount(const int pacmanCnt) const {
    if (m_coinsCnt == 0 || pacmanCnt != 1) {
        return false;
    }
    return true;
}

void CMap::resetData() {
    m_ghostSpawnpoints.clear();
    m_chars.clear();
    m_teleportPositions.clear();
    m_coinsCnt = 0;
}

void CMap::charsToTiles() {
    for (size_t row = 0; row < m_rowMax; row++) {
        std::vector<std::unique_ptr<CTile>> tileRow;
        for (size_t column = 0; column < m_columnMax; column++) {
            char c = m_chars[row][column];

            if (c == '.') {
                tileRow.emplace_back(std::make_unique<CCoin>(CPosition(row, column), '.'));
            } else if (c == '@') {
                tileRow.emplace_back(std::make_unique<CCherry>(CPosition(row, column), m_difficulty.getEatingLen(),
                                                               '@'));
            } else if (c == '#') {
                tileRow.emplace_back(std::make_unique<CWall>(CPosition(row, column), '#'));
            } else if (c == 'T') {
                size_t lastId = m_teleportPositions.size() - 1;
                tileRow.emplace_back(std::make_unique<CTeleport>(CPosition(row, column), m_teleportPositions[lastId],
                                                                 'T'));
                m_teleportPositions.pop_back();
            } else if (c == ' ') {
                tileRow.emplace_back(std::make_unique<CEmpty>(CPosition(row, column), ' '));
            } else if (c == 'g') {
                tileRow.emplace_back(std::make_unique<CGhostSpawn>(CPosition(row, column), 'g'));
            } else if (c == 'p') {
                tileRow.emplace_back(std::make_unique<CPacmanSpawn>(CPosition(row, column), 'p'));
            }
        }
        m_tiles.emplace_back(std::move(tileRow));
    }
}

void CMap::update(const CPacMan &pacman) {
    unsigned int row = pacman.m_currPosition.m_row;
    unsigned int column = pacman.m_currPosition.m_column;
    if (!pacman.inSpawn() && !pacman.m_teleported) {
        m_tiles[row].erase(m_tiles[row].begin() + column);
        m_tiles[row].emplace(m_tiles[row].begin() + column, std::make_unique<CEmpty>(CPosition(row, column), ' '));
    }
}

void CMap::callForEffect(CPacMan &pacman) const {
    this->getTile(pacman.m_currPosition)->doEffect(pacman);
}

void CMap::backToMapSelection() const {
    std::cout << "Press 'enter' to return to map selection..." << std::endl;
    std::cin.ignore().ignore();
}

void CMap::clearConsole() const {
    std::cout << "\033[2J\033[H";
}

unsigned int CMap::getCoinsCnt() const {
    return m_coinsCnt;
}

void CMap::printTile(const CPosition &position) const {
    this->getTile(position)->print();
}

const std::unique_ptr<CTile> &CMap::getTile(const CPosition &position) const {
    return m_tiles[position.m_row][position.m_column];
}

unsigned CMap::getRowCnt() const {
    return m_rowMax;
}

unsigned int CMap::getColumnCnt() const {
    return m_columnMax;
}

void CMap::spawnPacman(CPacMan &pacman) const {
    pacman.spawn(m_pacmanSpawnpoint);
}

bool CMap::newPosIfPossible(CPosition &position, int direction) const {
    CPosition tmpPos = position;
    if (direction == 0) {
        if (position.m_row != 0 && this->getTile(tmpPos.up())->canStepOn()) {
            position.m_row--;
            return true;
        }
    } else if (direction == 1) {
        if (position.m_column != 0 && this->getTile(tmpPos.left())->canStepOn()) {
            position.m_column--;
            return true;
        }
    } else if (direction == 2) {
        if (position.m_row != m_rowMax - 1 && this->getTile(tmpPos.down())->canStepOn()) {
            position.m_row++;
            return true;
        }
    } else {
        if (position.m_column != m_columnMax - 1 && this->getTile(tmpPos.right())->canStepOn()) {
            position.m_column++;
            return true;
        }
    }
    return false;
}

std::vector<std::pair<CPosition, char>> CMap::getGhosts() const {
    return m_ghosts;
}

