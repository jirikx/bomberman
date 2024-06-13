#pragma once
#include "Application.hpp"
#include "LeaderBoard.hpp"

/**
 * @brief Class which handles command line arguments passed to the program
 */
class InputHandler {
public:
    InputHandler();

    ~InputHandler();

    /**
     * @brief Chooses possible thing to do
     *
     * @param argc number of arguments
     * @param argv arguments themselves
     */
    void init(int argc, char **argv) const;

private:
    /**
     * @brief Starts the application with Bomberman game
     *
     * @param configPath is a path to the game config
     * @param leaderBoardPath is a path to the file with results (leaderboard)
     */
    void startApplication(const std::string &configPath, const std::string &leaderBoardPath) const;

    /**
     * @brief Just shows the leaderboard
     *
     * @param path to the file with results (leaderboard)
     */
    void showLeaderBoard(const std::string &path) const;

    static const std::string DEFAULT_CONFIG_PATH;
    static const std::string DEFAULT_LEADERBOARD_PATH;
};