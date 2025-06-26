#pragma once

#include "CGhost.h"

/**
 * Derived class from class CGhost representing pattern ghost.
 */
class CPatternGhost : public CGhost {

public:
    CPatternGhost() = delete;

    /**
     * Constructor receiving the position, speeds of the ghost and char representing the pattern ghost.
     * @param position
     * @param speed
     * @param ghostChar
     */
    CPatternGhost(const CPosition &position, int speed, int frightSpeed, char ghostChar);

    /**
     * Method that (depending on a mode) moves pattern ghost in certain pattern or away from pacman.
     * @param map
     * @param pacmanPos
     */
    void move(const CMap &map, const CPosition &pacmanPos) override;

    /**
     * Method that prints out the pattern ghost as variable m_ghostChar.
     */
    void print() const override;

private:
    /**
     * Method that determines whether Pacman is next to ghost.
     * @param pacmanPos
     * @param map
     * @returns true if pacman is next to ghost, false otherwise
     */
    bool isPacmanNearby(const CPosition &pacmanPos, const CMap &map) const;
};