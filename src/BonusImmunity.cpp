#include "BonusImmunity.hpp"

BonusImmunity::BonusImmunity()
  : Bonus() {
    m_Name = "Immunity against own bombs";
}

void BonusImmunity::activateBonus(PlayerStats &playerStats) {
    playerStats.hasImmunity = true;
}
