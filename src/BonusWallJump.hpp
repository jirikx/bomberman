#pragma once
#include "Bonus.hpp"

/**
 * @brief Gives the ability to jump over a wall m_JumpCount times
 * 
 */
class BonusWallJump : public Bonus {
public:
    explicit BonusWallJump(int jumpCount = 5);

    void activateBonus(PlayerStats &playerStats) override;

private:
    int m_JumpCount;
};