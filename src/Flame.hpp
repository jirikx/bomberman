#pragma once
#include "Tile.hpp"
#include <memory>

/**
 * @brief Flame is an object which can cause damage to other players
 *
 * It is created as an result of the bomb explosion
 */
class Flame : public Tile {
public:
    /**
     * @brief Constructor
     *
     * @param coords spawn point of the flame
     * @param ownerId is an ID of the player who created bomb which created the flame
     * @param duration is a duration of the flame in game ticks
     */
    Flame(Coords coords, size_t ownerId, int duration);

    /**
     * @brief Decrements duration of the flame
     *
     * @return true if the flame should be active, false otherwise
     */
    bool update();

    size_t m_OwnerId;

private:
    int m_TimeDuration;
};