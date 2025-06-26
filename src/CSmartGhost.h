#pragma once

#include <map>

#include "CGhost.h"

/**
 * Derived class from class CGhost representing smart ghost.
 */
class CSmartGhost : public CGhost {

public:
    CSmartGhost() = delete;

    /**
     * Constructor receiving the position speeds of the ghost and char representing the smart ghost.
     * @param position
     * @param speed
     * @param ghostChar
     */
    CSmartGhost(const CPosition &position, int speed, int frightSpeed, char ghostChar);

    /**
     * Method that (depending on a mode) moves smart ghost using BFS algorithm or away from pacman.
     * @param map
     * @param pacmanPos
     */
    void move(const CMap &map, const CPosition &pacmanPos) override;

    /**
     * Method that prints out the smart ghost as variable m_ghostChar.
     */
    void print() const override;

private:

    /**
     * Method that performs a breadth-first search algorithm until it encounters pacman position.
     * @param map
     * @param pacmanPos
     * @param childParent
     * @param found
     */
    void bfsSearch(const CMap& map, const CPosition& pacmanPos, std::map<CPosition, CPosition>& childParent,
                   bool &found) const;

    /**
     * Method that find the next move for smart ghost based on given path.
     * @param parents
     * @param goal
     * @returns new position for smart ghost
     */
    CPosition findMove(const std::map<CPosition, CPosition> &childParent, const CPosition &pacmanPos);

    /**
     * Method that finds path between Pacman and smart ghost based on given child-parent map of positions
     * @param childParent
     * @param pacmanPos
     * @returns vector of positions representing path
     */
    std::vector<CPosition> findPath(const std::map<CPosition, CPosition> &childParent, const CPosition &pacmanPos);
};