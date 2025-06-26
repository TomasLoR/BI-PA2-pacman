#pragma once

#include "CTile.h"

/**
 * Derived class from class CTile representing cherry tile.
 */
class CCherry : public CTile {
public:
    CCherry() = delete;

    /**
     * Constructor receiving the position of the tile, the length of the bonus and char representing the cherry.
     * @param position
     * @param bonusLen
     * @param charTile
     */
    CCherry(const CPosition &position, int bonusLen, char charTile);

    ~CCherry() override = default;

    /**
     * Method that prints out the cherry tile as variable m_tileChar.
     */
    void print() const override;

    /**
     * Method that gives information about walkability of cherry tile.
     * @returns true
     */
    bool canStepOn() const override;

    /**
     * Method that applies the effect of the cherry tile on the PacMan and prints out info message.
     * @param pacman
     */
    void doEffect(CPacMan &pacman) const override;

private:
    int m_score = 5;
    int m_bonusLen;
};
