#pragma once
#include "Bonus.hpp"

/**
 * @brief Make the player immune against his own bombs
 * 
 */
class BonusImmunity : public Bonus {
public:
    BonusImmunity();

    void activateBonus(PlayerStats &playerStats) override;
};