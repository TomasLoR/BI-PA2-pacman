#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing pacman spawnpoint tile.
 */

class CPacmanSpawn : public CTile {

public:
    CPacmanSpawn() = delete;

    /**
     * Constructor receiving the position of the tile and char representing the Pacman spawnpoint.
     * @param position
     * @param charTile
     */
    CPacmanSpawn(const CPosition &position, char charTile);

    /**
     * Method that prints out the pacman spawnpoint tile as variable m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of pacman spawnpoint tile.
     * @returns true
     */
    bool canStepOn() const override;

    /**
     * Method that applies the effect of the pacman spawnpoint tile on the PacMan and prints out info message.
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:
    int m_score = 1;
};