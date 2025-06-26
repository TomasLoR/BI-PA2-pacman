#include "CGame.h"

CGame::CGame(const CDifficulty &difficulty) : m_difficulty(difficulty) {}

int CGame::start() {
    introduction();
    m_map.create(m_difficulty);
    if (std::cin.eof()) {
        return 0;
    }
    setUpPacman();
    setUpGhosts();
    makeTurns();
    return m_pacman.m_score;
}

void CGame::introduction() const {
    clearConsole();
    std::cout << "Legend of chars in game:" << std::endl
              << "Pacman = P" << std::endl << "Pacman spawnpoint = p (+1 score if pacman can eat)" << std::endl
              << "Frightened ghost = f (+100 score)" << std::endl << "Dumb ghost = D" << std::endl << "Smart ghost = S"
              << std::endl << "Pattern ghost = R" << std::endl << "Ghost spawnpoint = g (+50 score)" << std::endl
              << "Coin = . (+1 score)" << std::endl << "Cherry = @ (+5 score)" << std::endl
              << "Teleport = T" << std::endl << "Wall = #" << std::endl
              << "--------------------------------------------------------------" << std::endl
              << "Controls: w = up, a = left, s = down, d = right" << std::endl
              << "--------------------------------------------------------------" << std::endl
              << "Press 'enter' to continue to map selection..." << std::endl;
    std::cin.ignore().ignore();
}

void CGame::setUpGhosts() {
    std::vector<std::pair<CPosition, char>> ghosts = m_map.getGhosts();
    int frightSpeed = m_difficulty.getFrightSpeed();

    for (const auto &ghost: ghosts) {
        if (ghost.second == 'D') {
            m_ghosts.emplace_back(
                    std::make_unique<CDumbGhost>(ghost.first, m_difficulty.getDumbSpeed(), frightSpeed, 'D'));
        } else if (ghost.second == 'R') {
            m_ghosts.emplace_back(
                    std::make_unique<CPatternGhost>(ghost.first, m_difficulty.getPatternSpeed(), frightSpeed, 'R'));
        } else if (ghost.second == 'S') {
            m_ghosts.emplace_back(
                    std::make_unique<CSmartGhost>(ghost.first, m_difficulty.getSmartSpeed(), frightSpeed, 'S'));
        }
    }
}

void CGame::setUpPacman() {
    m_map.spawnPacman(m_pacman);
    m_pacman.m_lives = m_difficulty.getLives();
}

void CGame::makeTurns() {

    while (!gameEnds()) {
        render();
        std::string direction;
        directionInput(std::cin, direction);
        if (std::cin.eof()) {
            break;
        }
        if (!validDirection(direction)) {
            std::cout << "Wrong input for direction, use only: w, a, s, d (one at the time)" << std::endl;
            continue;
        }
        pacmanMovement(direction);
        ghostMovement();
        clearConsole();
        m_map.callForEffect(m_pacman);
        handleGhostModes();
        m_map.update(m_pacman);
    }
}

bool CGame::gameEnds() {
    if (m_pacman.m_collectedCoins == m_map.getCoinsCnt()) {
        return true;
    }
    if (m_pacman.m_lives == 0) {
        m_pacman.m_score *= -1;
        return true;
    }
    return false;
}

void CGame::render() const {
    unsigned int ghostId = 0;

    for (size_t row = 0; row < m_map.getRowCnt(); row++) {
        for (size_t column = 0; column < m_map.getColumnCnt(); column++) {
            if (isPacman(CPosition(row, column))) {
                m_pacman.print();
            } else if (isGhost(CPosition(row, column), ghostId)) {
                m_ghosts[ghostId]->print();
            } else {
                m_map.printTile(CPosition(row, column));
            }
        }
        std::cout << std::endl;
    }
    m_pacman.printStats();
}

void CGame::directionInput(std::istream &input, std::string &direction) const {
    input >> direction;
}

bool CGame::validDirection(std::string &direction) const {
    if (direction != "w" && direction != "s" && direction != "a" && direction != "d") {
        return false;
    }
    return true;
}

void CGame::pacmanMovement(const std::string &direction) {
    int directionId = convertDirection(direction);
    CPosition newPos = m_pacman.m_currPosition;
    if (m_map.newPosIfPossible(newPos, directionId) && m_map.getTile(newPos)->canStepOn()) {
        m_pacman.move(newPos);
    }
}

void CGame::handleGhostModes() {
    if (m_pacman.m_eatingTurns == m_difficulty.getEatingLen() && !m_frightMode) {
        switchMode();
        m_frightMode = true;
    } else if (m_pacman.m_eatingTurns == 0 && m_frightMode) {
        switchMode();
        m_frightMode = false;
        m_pacman.m_canEat = false;
    }
    if (m_pacman.m_eatingTurns != 0) {
        m_pacman.m_eatingTurns--;
    }
}

bool CGame::isPacman(const CPosition &position) const {
    if (position == m_pacman.m_currPosition) {
        return true;
    }
    return false;
}

bool CGame::isGhost(const CPosition &position, unsigned int &ghostId) const {
    for (size_t i = 0; i < m_ghosts.size(); i++) {
        if (position == m_ghosts[i]->getCurrPos()) {
            ghostId = i;
            return true;
        }
    }
    return false;
}

void CGame::ghostMovement() {
    for (size_t i = 0; i < m_ghosts.size(); i++) {
        m_ghosts[i]->move(m_map, m_pacman.m_currPosition);
        if (m_ghosts[i]->getCurrPos() == m_pacman.m_currPosition) {
            if (resolveCollision(i)) {
                break;
            }
        }
    }
}

bool CGame::resolveCollision(unsigned int id) {
    if (m_pacman.m_canEat) {
        m_ghosts[id]->respawn();
        m_pacman.m_score += 100;
        return false;
    } else {
        for (const auto &m_ghost: m_ghosts) {
            m_ghost->respawn();
        }
        m_pacman.m_lives--;
        m_pacman.respawn();
        if (m_pacman.m_lives != 0) {
            m_pacman.losingLifeNotification();
        }
        return true;
    }
}

void CGame::switchMode() {
    for (const auto &m_ghost: m_ghosts) {
        m_ghost->toggleFrightened();
    }
}

int CGame::convertDirection(const std::string &direction) const {
    int value;

    switch (direction[0]) {
        case 'w':
            value = 0;
            break;
        case 'a':
            value = 1;
            break;
        case 's':
            value = 2;
            break;
        case 'd':
            value = 3;
            break;
        default:
            value = -1;
            break;
    }
    return value;
}

void CGame::clearConsole() const {
    std::cout << "\033[2J\033[H";
}