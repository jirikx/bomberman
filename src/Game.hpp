#pragma once
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <ncurses.h>
#include "PlayerHuman.hpp"
#include "GameBoard.hpp"
#include "InfoBoard.hpp"
#include "Bonus.hpp"

/**
 * @brief Represents an instance of the game which is being played
 *
 */
class Game {
public:
    Game(const std::shared_ptr<GameBoard> &gameBoard, const std::vector<std::shared_ptr<AbstractPlayer>> &players,
         const std::vector<std::pair<int, std::shared_ptr<Bonus>>> &bonusChances);

    /**
     * @brief Render the first frame of the game
     *
     */
    void start();

    /**
     * @brief Render current frame
     *
     */
    void render();

    /**
     * @brief Performs another game tick
     *
     * @return true if the game should continue, false if it ended
     */
    bool update();

    /**
     * @brief Returns the players who won the game
     *
     * @return vector of winners, can be empty if nobody won
     */
    std::vector<std::pair<std::string, size_t>> getWinners() const;
private:
    /**
     * @brief This method lets all active/alive players to do some allowed action
     *
     * @return true when there are still some active players, false if not
     */
    bool updatePlayers();

    /**
     * @brief Lets the player plant the bomb
     *
     * Only the player on correct position with some free bombs can plant the bomb
     * @param player is a player who wants to plant the bomb
     */
    void handleBombPlant(const std::shared_ptr<AbstractPlayer> &player);

    /**
     * @brief Lets the player do desired movement if it's possible
     *
     * @param player is a player who wants to move
     * @param action is a movement action
     */
    void handleMovement(const std::shared_ptr<AbstractPlayer> &player, EAction action);

    /**
     * @brief Try to apply bonus on the player based on the random chance
     *
     * Rest of tries is thrown away after the player gets any bonus
     * @param player player who might get the bonus
     * @param tries number of tries to get the bonus
     */
    void tryGetBonus(const std::shared_ptr<AbstractPlayer> &player, size_t tries);

    /**
     * @brief Check any possible collisions with objects that might damage the player
     *
     * @param player someone who is colliding with other objects
     */
    void checkDeadlyCollisions(const std::shared_ptr<AbstractPlayer> &player);

    std::shared_ptr<GameBoard> m_GameBoard;
    std::shared_ptr<InfoBoard> m_InfoBoard;
    std::vector<std::shared_ptr<AbstractPlayer>> m_Players;
    std::vector<std::pair<int, std::shared_ptr<Bonus>>> m_BonusChances;
    std::map<std::shared_ptr<AbstractPlayer>, std::shared_ptr<Bonus>, CompareById> m_LastPlayerBonus;
};