#include "BonusStrongBomb.hpp"

BonusStrongBomb::BonusStrongBomb(int explosionPerimeter)
  : Bonus(), m_ExplosionPerimeter(explosionPerimeter) {
    m_Name = "Stronger bombs";
}

void BonusStrongBomb::activateBonus(PlayerStats &playerStats) {
    if (m_ExplosionPerimeter > playerStats.bombRange)
        playerStats.bombRange = m_ExplosionPerimeter;
}
