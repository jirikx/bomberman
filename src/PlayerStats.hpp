#pragma once

/**
 * @brief A simple structure which stores the statistics of the player
 *
 */
struct PlayerStats {
    PlayerStats();

    PlayerStats(int hp, int freeBombs, int wallJumpCount, bool hasImmunity, int bombRange);

    int hp;
    int freeBombs;
    int wallJumpCount;
    bool hasImmunity;
    int bombRange;
};
