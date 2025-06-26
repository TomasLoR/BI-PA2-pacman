#pragma once

#include "CMap.h"

/**
 * Pure abstract class representing ghost.
 */
class CGhost {

public:
    /**
     * Constructor receiving the position, speeds of the ghost and char representing the ghost.
     * @param position
     * @param startSpeed
     */
    CGhost(const CPosition &position, int startSpeed, int frightStartSpeed, char ghostChar);

    /**
     * Virtual destructor that allows proper destruction of the derived class objects.
     */
    virtual ~CGhost() = default;

    /**
     * Pure virtual method that moves with the ghost based on implementation in the derived class.
     * @param map
     * @param pacmanPos
     */
    virtual void move(const CMap &map, const CPosition &pacmanPos) = 0;

    /**
     * Pure virtual method that prints out ghost based on implementation in the derived class.
     */
    virtual void print() const = 0;

    /**
     * Method that sets m_currPosition variable to value of m_startPosition variable.
     */
    void respawn();

    /**
     * Method that changes boolean value of m_frightened to the opposite
     */
    void toggleFrightened();

    /**
    * Getter method that allows accessing the current position of the ghost.
    * @returns const CPosition&
    */
    const CPosition& getCurrPos () const;

protected:
    /**
     * Method that updates the value of m_currSpeed variable.
     */
    void updateSpeedCnt();

    /**
     * Method that resets current speed to starting speed.
     */
    void resetSpeedCnt();

    /**
     * Method that checks for collision between Pacman and ghost.
     * @param pacmanPos
     * @returns true if Pacman has same Position as ghost, false otherwise
     */
    bool isCollision (const CPosition &pacmanPos) const;

    /**
     * Method that moves ghost further from Pacman.
     * @param map
     * @param pacmanPos
     */
    void frightenedMovement(const CMap &map, const CPosition &pacmanPos);

    /**
    * Method that calculates manhattan distance between Pacman and ghost
    * @param ghostPos
    * @param pacmanPos
    * @returns the calculated distance
    */
    unsigned int ghostPacmanDistance(const CPosition &ghostPos, const CPosition &pacmanPos) const;

    /**
     * Method that inserts potential moves to @param[out] moves.
     * @param map
     * @param pacmanPos
     * @param moves
     */
    void prepMoves(const CMap &map, const CPosition &pacmanPos, std::vector<std::pair<CPosition, unsigned int>> &moves);

    /**
    * Method used as comparator function for sorting moves based on their distances from pacman in descending order.
    * @param m1
    * @param m2
    * @returns true if m1's distance is greater than m2's score, false otherwise
    */
    static bool compareMoves(const std::pair<CPosition, unsigned int> &m1,
                             const std::pair<CPosition, unsigned int> &m2);

    int m_startSpeed{};
    CPosition m_startPosition{};
    int m_frightStartSpeed{};
    char m_ghostChar{};
    int m_currSpeed{};
    int m_frightCurrSpeed{};
    CPosition m_currPosition{};
    char m_frightChar = 'f';
    bool m_frightened = false;
};