#include "BonusExtraHp.hpp"

BonusExtraHp::BonusExtraHp(int hpCount)
  : Bonus(), m_HpCount(hpCount) {
    m_Name = "Extra HP";
}

void BonusExtraHp::activateBonus(PlayerStats &playerStats) {
    playerStats.hp += m_HpCount;
}
