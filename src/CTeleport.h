#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing teleport tile.
 */
class CTeleport : public CTile {
public:
    CTeleport() = delete;

    /**
     * Constructor receiving the position of the teleport tile, its destination and the char representing the teleport.
     * @param position
     * @param positionToTp
     * @param charTile
     */
    CTeleport(const CPosition &position, const CPosition &positionToTp, char charTile);

    ~CTeleport() override = default;

    /**
     * Method that prints out the teleport tile as variable m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of teleport tile.
     * @returns true
     */
    bool canStepOn() const override;

    /**
     * Method that applies the effect of the teleport tile on the PacMan and prints out info message.
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:
    CPosition m_positionToTp;
};