#pragma once
#include "EAction.hpp"
#include "Coords.hpp"
#include "GameBoard.hpp"
#include "PlayerStats.hpp"
#include <string>

/**
 * @brief Class encapsulating the data about each Player of the game.
 *
 * The idea is that it will be manipulated mainly by outsiders and the
 * class itself shouldn't contain much game logic.
 */
class AbstractPlayer {
public:
    /**
     * @brief Constructor
     *
     * @param hp starting hit points
     * @param bombs disposable bombs to use
     * @param coords is starting position of the player
     */
    AbstractPlayer(int hp, int bombs, Coords coords);

    /**
     * @brief Constructor
     *
     * @param stats of the player
     * @param coords is starting position of the player
     * @param texture texture which is visible on the game board
     * @param nickname player's name
     */
    AbstractPlayer(const PlayerStats &stats, const Coords &coords, char texture, const std::string &nickname);

    virtual ~AbstractPlayer();

    /**
     * @brief Get the action from further specified source
     *
     * @return EAction is the action which the player wants to do
     */
    virtual EAction updateAction() = 0;

    /**
     * @brief Gives this player specified damage
     *
     * @param damage
     * @return true if the player died after receiving damage
     * @return false if the player survived
     */
    bool getHit(int damage);

    /**
     * @brief Gives this player specified damage
     *
     * @return true if the player is alive, false otherwise
     */
    bool isAlive() const;

    /**
     * @brief Tells if this player has immunity against specified player
     *
     * @param player to look at
     * @return true if this player is immune, false otherwise
     */
    bool isImmuneAgainst(const std::shared_ptr<AbstractPlayer> &player) const;

    /**
     * @brief Tells if the game should save score from this player to the leaderboard
     *
     * @return true if the score should be saved, false otherwise
     */
    bool participatesInLeaderboard() const;

    PlayerStats m_Stats;
    int m_Score;
    size_t m_Id;
    Coords m_Coords;
    char m_Texture;
    std::string m_NickName;

protected:
    bool m_ParticipatesInLeaderboard;
};

struct CompareById {
    bool operator()(const std::shared_ptr<AbstractPlayer> &lhs, const std::shared_ptr<AbstractPlayer> &rhs) const;
};