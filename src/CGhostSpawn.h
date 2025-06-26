#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing ghost spawnpoint tile.
 */
class CGhostSpawn : public CTile {

public:
    CGhostSpawn() = delete;

    /**
     * Constructor receiving the position of the tile and char representing the ghost spawnpoint.
     * @param position
     * @param charTile
     */
    CGhostSpawn(const CPosition &position, char charTile);

    /**
     * Method that prints out the ghost spawnpoint tile as variable m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of ghost spawnpoint tile.
     * @return
     */
    bool canStepOn() const override;

    /**
     * Method that applies the effect of the ghost spawnpoint tile on the PacMan and prints out info message.
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:
    int m_score = 50;
};