#pragma once

#include "CDifficulty.h"
#include "CDumbGhost.h"
#include "CSmartGhost.h"
#include "CPatternGhost.h"

/**
 * Method representing the game itself managing the interactions between different game components.
 */
class CGame {
public:
    /**
     * Constructor receiving the game difficulty.
     * @param difficulty
     */
    explicit CGame(const CDifficulty &difficulty);

    CGame(const CGame &) = delete;

    CGame &operator=(const CGame &) = delete;

    ~CGame() = default;

    /**
     * Method that starts the game session.
     * @returns int value of score <= 0 if player lost, > 0 otherwise
     */
    int start();

private:
    /**
     * Method that prints out introduction info about the game characters..
     */
    void introduction() const;

    /**
     * Method that renders curr state of the game.
     */
    void render() const;

    /**
     * Method that checks if given position is position of the Pacman.
     * @param position
     * @returns true if the given position is same as the Pacman's.
     */
    bool isPacman(const CPosition &position) const;

    /**
     * Method that checks if given position is position of the ghost with the given id.
     * @param position
     * @param ghostId
     * @return true if the given position is same as the ghost's.
     */
    bool isGhost(const CPosition &position, unsigned int &ghostId) const;

    /**
     * Method that sets up all the ghosts for the first time.
     */
    void setUpGhosts();

    /**
     * Method that sets up Pacman for the first time.
     */
    void setUpPacman();

    /**
     * Method that validates the user's input for direction.
     * @param direction
     * @returns true if the direction is valid, false otherwise
     */
    bool validDirection(std::string &direction) const;

    /**
     * Method that manages everything happening in one turn of the game
     */
    void makeTurns();

    /**
     * Method that manages users input for direction.
     * @param input
     * @param direction
     */
    void directionInput(std::istream &input, std::string &direction) const;

    /**
     * Method that converts valid direction symbol to its int value.
     * @param direction
     * @returns int value of direction
     */
    int convertDirection(const std::string &direction) const;

    /**
     * Method that manages Pacman's movement.
     * @param direction
     */
    void pacmanMovement(const std::string &direction);

    /**
     * Method that manages ghosts's movement.
     */
    void ghostMovement();

    /**
     * Method that resolve collision between ghost with given id and Pacman.
     * @param id
     * @returns true if Pacman ate ghost, false if ghost killed Pacman
     */
    bool resolveCollision(unsigned int id);

    /**
     * Method that manages changes in ghost modes.
     */
    void handleGhostModes();

    /**
    * Method that switches mode of all the ghosts.
    */
    void switchMode();

    /**
     * Method that checks game-ending conditions.
     * @returns true if game ending conditions are met, false otherwise
     */
    bool gameEnds();

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void clearConsole() const;

    CMap m_map;
    CPacMan m_pacman;
    std::vector<std::unique_ptr<CGhost>> m_ghosts;
    bool m_frightMode = false;
    CDifficulty m_difficulty;
};