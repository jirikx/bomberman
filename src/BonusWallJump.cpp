#include "BonusWallJump.hpp"

BonusWallJump::BonusWallJump(int jumpCount)
  : Bonus(), m_JumpCount(jumpCount) {
    m_Name = "Extra wall jumps";
}

void BonusWallJump::activateBonus(PlayerStats &playerStats) {
    playerStats.wallJumpCount += m_JumpCount;
}
