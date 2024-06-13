#pragma once
#include <memory>
#include <vector>
#include "Coords.hpp"
#include "Flame.hpp"

/**
 * @brief Represents a bomb on our game board
 *
 * This object won't cause any damage, but it creates
 * flames which will do.
 */
class Bomb : public Tile {
public:
    /**
     * @brief Constructor
     *
     * @param coords where the bomb is spawned
     * @param ownerId is an ID of the player who planted it
     * @param timeLimit game ticks after which the bomb explodes
     * @param range of the explosion
     */
    Bomb(Coords coords, size_t ownerId, int timeLimit, int range);

    Bomb(const Bomb &bomb);

    /**
     * @brief Decrements time to explode
     *
     */
    void update();

    /**
     * @brief Tells if the bomb should explode by now
     *
     * @return true if the bomb should explode, false otherwise
     */
    bool shouldExplode() const;

    size_t m_OwnerId;
    int m_TimeToExplode; // Bomb explodes after certain period of time (game ticks)
    int m_Range;         // Range of the bomb explosion, it's a perimeter around m_Coords
};