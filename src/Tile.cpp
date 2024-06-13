#include "Tile.hpp"

Tile::Tile() : Tile({0,0}, ' ') {}

Tile::Tile(const Coords &coords, char texture)
  : m_Coords(coords), m_Texture(texture) {}

Tile::~Tile() = default;

Coords Tile::getCoords() const {
    return m_Coords;
}