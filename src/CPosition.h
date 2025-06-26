#pragma once

#include <iostream>

/**
 * Class representing position in 2D space.
 */
class CPosition {
public:
    CPosition() = default;

    /**
     * Constructor receiving row and column of certain entity.
     * @param currRow
     * @param currColumn
     */
    CPosition(unsigned int row, unsigned int column);

    CPosition(const CPosition &) = default;

    CPosition &operator=(const CPosition &) = default;

    ~CPosition() = default;

    /**
     * Method used as equality comparison operator for CPosition objects.
     * @param other
     * @returns true if the positions are equal, false otherwise
     */
    bool operator==(const CPosition &other) const;

    /**
     * Method used as inequality comparison operator for CPosition objects.
     * @param other
     * @returns true if the positions are not equal, false otherwise
     */
    bool operator!=(const CPosition &other) const;

    /**
     * Method used as less-than comparison operator for CPosition objects.
     * @param other
     * @returns true if this position is less than the other position, false otherwise
     */
    bool operator<(const CPosition &other) const;

    /**
     * Method used as compound addition operator for CPosition objects.
     * @param other
     * @returns reference to the updated CPosition object
     */
    CPosition &operator+=(const CPosition &other);

    /**
     * Friend function used for streaming a CPosition object to an output stream.
     * @param os
     * @param position
     * @returns reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const CPosition &position);

    /**
     * Moves the position up (decrements the row).
     * @returns reference to the output stream
     */
    const CPosition &up();

    /**
     * Moves the position left (decrements the column).
     * @returns reference to the updated CPosition object
     */
    const CPosition &left();

    /**
    * Moves the position down (increments the row).
    * @returns reference to the updated CPosition object
    */
    const CPosition &down();

    /**
     * Moves the position right (increments the column).
     * @returns reference to the updated CPosition object
     */
    const CPosition &right();

    unsigned int m_row{};
    unsigned int m_column{};
};