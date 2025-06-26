#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing empty tile.
 */
class CEmpty : public CTile {

public:
    CEmpty() = delete;

    /**
     * Constructor receiving the position of the empty tile and char representing the empty space.
     * @param position
     * @param charTile
     */
    CEmpty(const CPosition &position, char charTile);

    /**
     * Method that prints out the wall tile as variable m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of wall tile.
     * @returns true
     */
    bool canStepOn() const override;

    /**
     * Method that prints out info message about the tile and pacman position.
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:

};