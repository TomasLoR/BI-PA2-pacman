#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing wall tile.
 */
class CWall : public CTile {
public:
    CWall() = delete;

    /**
     * Constructor receiving the position of the wall tile and char representing the wall.
     * @param position
     * @param charTile
     */
    CWall(const CPosition &position, char charTile);

    ~CWall() override = default;

    /**
     * Method that prints out the wall tile as m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of wall tile.
     * @returns false
     */
    bool canStepOn() const override;

    /**
     * Method that should not be ever called on CTile, however if it happens it prints out info message
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:

};