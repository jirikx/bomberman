#pragma once
#include "EAction.hpp"
#include <cstddef>

/**
 * @brief Represents {x,y} coordinates on the screen
 *
 */
struct Coords {
    Coords(int x, int y);

    bool operator<(const Coords &rhs) const;

    bool operator==(const Coords &rhs) const;

    Coords operator+(const Coords &rhs) const;

    Coords operator-(const Coords &rhs) const;

    int x;
    int y;
};

/**
 * @brief Calculates new coordinates after moving in specific direction
 *
 * If the action doesn't tell any direction, the coordinates don't change
 * @param coords original coordinates
 * @param action specifies the direction
 * @return coordinates after move
 */
Coords operator+(Coords coords, EAction action);