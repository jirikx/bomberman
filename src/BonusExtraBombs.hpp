#pragma once
#include "Bonus.hpp"

/**
 * @brief Gives extra bombs to the player
 *
 */
class BonusExtraBombs : public Bonus {
public:
    explicit BonusExtraBombs(int bombCount = 3);

    void activateBonus(PlayerStats &playerStats) override;

private:
    int m_BombCount;
};