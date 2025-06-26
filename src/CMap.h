#pragma once

#include <vector>
#include <memory>

#include "CCoin.h"
#include "CCherry.h"
#include "CWall.h"
#include "CTeleport.h"
#include "CEmpty.h"
#include "CDifficulty.h"
#include "CGhostSpawn.h"
#include "CPacmanSpawn.h"

/**
 * Class representing map in the Pacman game
 */
class CMap {
public:
    CMap() = default;

    CMap(const CMap &) = delete;

    CMap &operator=(const CMap &) = delete;

    ~CMap() = default;

    /**
     * Method that creates a new map with the specified difficulty.
     * @param difficulty
     */
    void create(const CDifficulty &difficulty);

    /**
     * Method that updates the map based on the current position of the Pacman.
     * @param pacman
     */
    void update(const CPacMan &pacman);

    /**
     * Method that calls for an effect on the tile with the same position as pacman.
     * @param pacman
     */
    void callForEffect(CPacMan &pacman) const;

    /**
     * Method that tries to move the given position based on given direction.
     * @param position
     * @param direction
     * @return
     */
    bool newPosIfPossible(CPosition &position, int direction) const;

    /**
     * Method that calls for printing the tile at the specified position.
     * @param position
     */
    void printTile(const CPosition &position) const;

    /**
     * Method that calls for Pacman spawning based on m_pacmanSpawnpoint member variable.
     * @param pacman
     */
    void spawnPacman(CPacMan &pacman) const;

    /**
    * Method that allows accessing the tile based on given position.
    * @param position
    * @returns a reference to the tile
    */
    const std::unique_ptr<CTile> &getTile(const CPosition& position) const;

    /**
     * Getter method that allows accessing the number of rows in the map.
     * @returns the number of rows
     */
    unsigned int getRowCnt() const;

    /**
     * Getter method that allows accessing the number of columns in the map.
     * @returns the number of columns
     */
    unsigned int getColumnCnt() const;

    /**
     * Getter method that allows accessing the number of coins in the map.
     * @returns the number of coins
     */
    unsigned int getCoinsCnt() const;

    /**
     * Getter method that allows accessing ghosts represented as chars and their position.
     * @returns ghosts represented as chars and their position
     */
    std::vector<std::pair<CPosition, char>> getGhosts() const;

private:
    /**
     * Method that reads the map name from the input stream.
     * @param input
     * @returns the map name
     */
    std::string receiveMapName(std::istream &input) const;

    /**
     * Method that converts the map name to a filename.
     * @param mapName
     */
    void nameToFilename(std::string &mapName) const;

    /**
     * Method that tries to load data from the map file.
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
     * Method that tries to load parameters from the map file.
     * @param inFile
     * @returns true if it loads successfully, false otherwise
     */
    bool loadParameters(std::ifstream &inFile);

    /**
     * Method that tries to load map itself from the map file.
     * @param inFile
     * @returns true if it loads successfully, false otherwise
     */
    bool loadMap(std::ifstream &inFile);

    /**
     * Method that resets member variables in case data loading failed midway.
     */
    void resetData();

    /**
     * Method that validates the desired number of coins and pacman spawnpoints in the map.
     * @param pacmanCnt
     * @returns true if the map has desired number of coin and pacman spawnpoints, false otherwise
     */
    bool validateTileCount(int pacmanCnt) const;

    /**
     * Method that converts valid map of chars to map of CTiles.
     */
    void charsToTiles();

    /**
     * Method that prompts user to press 'enter' to return to map selection.
     */
    void backToMapSelection() const;

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void clearConsole() const;

    CDifficulty m_difficulty;
    std::vector<std::vector<char>> m_chars;
    std::vector<CPosition> m_teleportPositions;
    std::vector<CPosition> m_ghostSpawnpoints;
    std::vector<std::pair<CPosition, char>> m_ghosts;
    std::vector<std::vector<std::unique_ptr<CTile>>> m_tiles;
    CPosition m_pacmanSpawnpoint;
    unsigned int m_coinsCnt = 0;
    unsigned int m_rowMax{};
    unsigned int m_columnMax{};
};