#pragma once
#include "AbstractPlayer.hpp"
#include <memory>

/**
 * @brief Player who is completely controlled by the computer
 *
 */
class PlayerComputer : public AbstractPlayer {
public:
    PlayerComputer(int hp, int bombs, const Coords &coords, const std::shared_ptr<AbstractPlayer> &enemy);

    /**
     * @brief Calculate the best action which gets the player
     *        closer to the m_Enemy
     *
     * @return calculated action
     */
    EAction updateAction() override;

private:
    /**
     * @brief This is someone who the player tries to kill by moving towards him
     *
     */
    std::shared_ptr<AbstractPlayer> m_Enemy;
};