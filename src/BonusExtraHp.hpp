#pragma once
#include "Bonus.hpp"

/**
 * @brief Gives extra hit points to the player
 *
 */
class BonusExtraHp : public Bonus {
public:
    explicit BonusExtraHp(int hpCount = 1);

    void activateBonus(PlayerStats &playerStats) override;

private:
    int m_HpCount;
};