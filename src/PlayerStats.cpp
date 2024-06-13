#include "PlayerStats.hpp"

PlayerStats::PlayerStats() = default;

PlayerStats::PlayerStats(int hp, int freeBombs, int wallJumpCount, bool hasImmunity, int bombRange)
  : hp(hp), freeBombs(freeBombs), wallJumpCount(wallJumpCount), hasImmunity(hasImmunity), bombRange(bombRange) {}