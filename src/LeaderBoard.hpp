#pragma once
#include "SceneManager.hpp"
#include <optional>
#include <vector>

/**
 * @brief Class used for storing game results and showing them to the user
 *
 */
class LeaderBoard : public SceneManager {
public:
    explicit LeaderBoard(const std::string &pathToLeaderBoard);

    /**
     * @brief Tries to write result to the leaderboard file
     *
     * @param result to write
     */
    void write(const std::pair<std::string, size_t> &result);

    /**
     * @brief Prints top results to the screen
     *
     * @param maxRows is the maximum number of rows to print
     */
    void print(int maxRows = 10);

private:
    /**
     * @brief Gets all the results from the leaderboard file and stores them to vector
     *
     * @return vector with parsed leaderboard results
     */
    std::vector<std::pair<std::string, size_t>> getResults();

    std::string m_PathToLeaderBoard;
};