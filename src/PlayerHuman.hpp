#pragma once
#include "GameBoard.hpp"
#include "AbstractPlayer.hpp"
#include <map>

/**
 * @brief Player controlled by the keyboard
 *
 */
class PlayerHuman : public AbstractPlayer {
public:
    PlayerHuman(const PlayerStats &stats, const Coords &coords, char texture, std::string &nickname,
                const std::map<int, EAction> &controls);

    PlayerHuman(int hp, int bombs, const std::string &nickname, Coords coords, const std::map<int, EAction> &controls);

    /**
     * @brief PlayerHuman waits for input from the keyboard and then picks
     *        an action according to it
     *
     * @return action which the player wants to do
     */
    EAction updateAction() override;

    std::map<int, EAction> m_Controls;
    std::shared_ptr<GameBoard> m_GameBoard;
};