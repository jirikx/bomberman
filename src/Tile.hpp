#pragma once
#include "Coords.hpp"

/**
 * @brief Represents a tile on the game board
 *
 * It is used as a base for f.e. bomb or flame
 */
class Tile {
public:
    Tile();
    
    Tile(const Coords &coords, char texture);

    virtual ~Tile();

    Coords getCoords() const;

    Coords m_Coords;
    char m_Texture;
};