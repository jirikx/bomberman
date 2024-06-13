#pragma once
#include <map>
#include <memory>
#include <optional>
#include "SceneManager.hpp"
#include "Bomb.hpp"

const char WALL_SOLID = '#';
const char WALL_DESTRUCTIBLE = '&';
const char TILE_EMPTY = ' ';

const int DEFAULT_BOMB_TIME = 3;
const int EXPLOSION_DURATION = 2;
const int DEFAULT_DAMAGE = 1;
const int KILL_POINTS = 10;

/**
 * @brief Represents a view of the game (graphics and tiles on the board)
 *
 */
class GameBoard : public SceneManager {
public:
    GameBoard(int height, int width);

    GameBoard(int height, int width, const std::map<Coords, bool> &walls);

    /**
     * @brief Prepares graphics side of the GameBoard
     *
     */
    void setup();

    /**
     * @brief Print walls, bombs and flames to the screen
     *
     */
    void printTiles();

    /**
     * @brief Determines further action based on the user input
     *
     * @param controls map for converting input to action
     * @return concrete action
     */
    EAction getAction(const std::map<int, EAction> &controls) const;

    /**
     * @brief Tells if the position with given coordinates is free
     *
     * @param coords position to check
     * @return true if it's free, false otherwise
     */
    bool canMoveTo(const Coords &coords) const;

    /**
     * @brief Adds a bomb on the GameBoard
     *
     * Also checks if it's possible to put a bomb there.
     * @param bomb to be added
     * @return true if the bomb was added, false otherwise
     */
    bool addBomb(const Bomb &bomb);

    /**
     * @brief Updates time to explode on all the active bombs
     *
     * Also checks if there were any destructible walls which
     * can potentially give a bonus to the player.
     * @return map where key is a player ID and value is number of tries
     *         which the player can use to try to get a bonus
     */
    std::map<size_t, size_t> updateBombs();

    /**
     * @brief Updates time to disappear on all active flames
     *
     * Any flame which existed for too long is erased
     */
    void updateFlames();

    /**
     * @brief Returns flame object on given coordinates
     *
     * @param coords where the flame should be
     * @return the flame if it was on given coords
     */
    std::optional<Flame> getFlameAt(const Coords &coords) const;

private:
    /**
    * @brief Adds a flame to the GameBoard if it's possible
    *
    * @param flame to be added
    * @return true if the flame was added, false otherwise
    */
    bool addFlame(const Flame &flame);

    /**
     * @brief Generates flames in all the explosion directions
     *
     * Flames are created only in horizontal and vertical lines, not diagonally
     * @param bomb from which come the flames
     * @return number of destroyed walls which can be potentially used to get bonus
     */
    size_t generateFlames(const Bomb &bomb);

    /**
     * @brief Create flames in direction specified by x and y
     *
     * @param bomb from which come the flames
     * @param x horizontal axis
     * @param y vertical axis
     * @return number of destroyed walls which can be potentially used to get bonus
     */
    size_t createFlamesInDirection(const Bomb &bomb, int x, int y);

    /**
     * @brief Map of all walls in the GameBoard
     *
     * True value = wall is destructible,
     * false value = wall is solid
     */
    std::map<Coords, bool> m_Walls;

    std::map<Coords, Bomb> m_Bombs;
    std::map<Coords, Flame> m_Flames;
};