#include "BonusExtraBombs.hpp"

BonusExtraBombs::BonusExtraBombs(int bombCount)
  : Bonus(), m_BombCount(bombCount) {
    m_Name = "Extra bombs";
}

void BonusExtraBombs::activateBonus(PlayerStats &playerStats) {
    playerStats.freeBombs += m_BombCount;
}
