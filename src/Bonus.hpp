#pragma once
#include "PlayerStats.hpp"
#include "EAction.hpp"

/**
 * @brief Bonus changes some attributes of the player
 *        based on the exact bonus implementation
 *
 * Bonus will be really available only to human players because they
 * are the only ones who will have some bombs to destroy walls, but 
 * maybe it will be also used by the AI in the future.
 */
class Bonus {
public:
    Bonus();

    virtual ~Bonus();

    /**
     * @brief Changes the player stats based on the bonus properties
     *
     * @param playerStats to be changed
     */
    virtual void activateBonus(PlayerStats &playerStats) = 0;

    /**
     * @brief Getter for the name of the bonus
     *
     * @return name of the bonus
     */
    const std::string &getName() const;

protected:
    std::string m_Name;
};