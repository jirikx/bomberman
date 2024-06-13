#include "Bomb.hpp"

Bomb::Bomb(Coords coords, size_t ownerId, int timeLimit, int range)
  : Tile(coords, 'b'), m_OwnerId(ownerId), m_TimeToExplode(timeLimit), m_Range(range) {}

Bomb::Bomb(const Bomb &bomb) = default;

void Bomb::update() {
    m_TimeToExplode--;
}

bool Bomb::shouldExplode() const {
    return m_TimeToExplode <= 0;
}
