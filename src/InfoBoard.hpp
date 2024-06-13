#pragma once
#include "SceneManager.hpp"
#include "AbstractPlayer.hpp"
#include <memory>

/**
 * @brief This class represents a window with relevant info
 *        about currently playing player
 *
 */
class InfoBoard : public SceneManager {
public:
    InfoBoard(int height, int width, int startY, int startX);

    /**
     * @brief Prepares the GameBoard for further usage
     *
     */
    void setup();

    /**
     * @brief Prints the name and texture of currently playing player
     *
     * @param player who is playing now
     */
    void printNowPlaying(const std::shared_ptr<AbstractPlayer> &player);

    /**
     * @brief Prints the name of the last bonus which was acquired by player
     *
     * @param bonusName name of the bonus
     */
    void printLastBonus(const std::string &bonusName);

    /**
     * @brief Clears the line which is used for displaying last bonus
     *
     */
    void clearLastBonus();
};