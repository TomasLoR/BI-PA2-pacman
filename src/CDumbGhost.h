#pragma once

#include "CGhost.h"

/**
 * Derived class from class CGhost representing dumb ghost.
 */

class CDumbGhost : public CGhost {

public:
    CDumbGhost() = delete;

    /**
     * Constructor receiving the position, speeds of the ghost and char representing the dumb ghost.
     * @param position
     * @param speed
     * @param ghostChar
     */
    CDumbGhost(const CPosition &position, int speed, int frightSpeed, char ghostChar);

    ~CDumbGhost() override = default;

    /**
     * Method that (depending on a mode) moves dumb ghost randomly or away from pacman.
     * @param map
     * @param pacmanPos
     */
    void move(const CMap &map, const CPosition &pacmanPos) override;

    /**
     * Method that prints out the dumb ghost as variable m_ghostChar.
     */
    void print() const override;

private:

};