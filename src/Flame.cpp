#include "Flame.hpp"

Flame::Flame(Coords coords, size_t ownerId, int duration)
  : Tile(coords, 'x'), m_OwnerId(ownerId), m_TimeDuration(duration) {}

bool Flame::update() {
    return --m_TimeDuration > 0;
}
