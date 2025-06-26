#pragma once

#include "CPacMan.h"

/**
 * Pure abstract class representing tile.
 */
class CTile {
public:
    CTile() = delete;

    /**
     * Constructor receiving the position of the tile and char representing the tile.
     * @param position
     * @param charTile
     */
    CTile(const CPosition &position, char charTile);

    /**
     * Virtual destructor that allows proper destruction of the derived class objects.
     */
    virtual ~CTile() = default;

    /**
     * Pure virtual method that prints out tile based on implementation in the derived class.
     */
    virtual void print() const = 0;

    /**
     * Pure virtual method that gives information about walkability of the tile from derived class.
     * @returns true if pacman can step on the tile, false otherwise
     */
    virtual bool canStepOn() const = 0;

    /**
     * Pure virtual method that executes the tile effect implemented in derived class.
     * @param pacman
     */
    virtual void doEffect(CPacMan &pacman) const = 0;

    /**
     * Getter method allows accessing the position of the tile.
     * @returns position of the tile
     */
    const CPosition& getPosition() const;

protected:

    CPosition m_position{};
    char m_tileChar{};
};