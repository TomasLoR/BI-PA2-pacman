#pragma once

#include "CPosition.h"

class CPacMan {

public:
    CPacMan() = default;

    /**
     * Explicit constructor receiving position of the Pacman.
     * @param position
     */
    explicit CPacMan(const CPosition &position);

    ~CPacMan() = default;

    /**
     * Method that moves pacman to new position.
     * @param newPosition
     */
    void move(const CPosition &newPosition);

    /**
     * Method that prints out Pacman as variable m_pacmanChar.
     */
    void print() const;

    /**
     * Method that changes Pacman's current position to starting position.
     */
    void respawn();

    /**
     * Method that initializes current and starting position of the Pacman.
     * @param position
     */
    void spawn(const CPosition &position);

    /**
     * Method that printsout stats about the Pacman.
     */
    void printStats() const;

    /**
     * Method that tells us if the Pacman is in the spawn or not.
     * @returns true if m_currPos == m_startPos, false otherwise
     */
    bool inSpawn() const;

    /**
     * Method that is called to print out message when pacman loses a life.
     */
    void losingLifeNotification() const;

    /**
     * Method that sends an escape sequence to the standard output stream to clear the console screen.
     */
    void cleanConsole() const;

    CPosition m_startPosition{};
    CPosition m_currPosition{};
    unsigned int m_collectedCoins = 0;
    unsigned int m_lives = 3;
    int m_eatingTurns = 0;
    int m_score = 0;
    bool m_teleported = false;
    bool m_canEat = false;
    char m_pacmanChar = 'P';
private:
};
