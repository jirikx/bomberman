#pragma once
#include <ncurses.h>
#include "Configuration.hpp"
#include "LeaderBoard.hpp"
#include "Game.hpp"

/**
 * @brief Main application class
 *
 */
class Application {
public:
    /**
     * @brief Starts application with parameters from previously parsed config
     *
     * @param config stores configuration previously specified in the file
     * @param leaderBoard writes application result into specified file
     */
    Application(const Configuration &config, const LeaderBoard &leaderBoard);

    ~Application();

    /**
     * @brief Starts the whole program
     *
     */
    void run();

private:
    /**
     * @brief Shows player the winner and writes it to the leaderboard
     *
     */
    void handleWinners();

    Game m_Game;
    bool m_IsRunning;
    Configuration m_Config;
    LeaderBoard m_LeaderBoard;
};