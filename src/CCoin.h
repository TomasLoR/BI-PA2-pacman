#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing coin tile.
 */
class CCoin : public CTile {
public:
    CCoin() = delete;

    /**
     * Constructor receiving the position of the coin tile and char representing the coin.
     * @param position
     * @param charTile
     */
    CCoin(const CPosition &position, char charTile);

    ~CCoin() override = default;

    /**
     * Method that prints out the coin tile as variable m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of coin tile.
     * @returns true
     */
    bool canStepOn() const override;

    /**
     * Method that applies the effect of the coin tile on the PacMan and prints out the info message.
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:
    int m_score = 1;

};