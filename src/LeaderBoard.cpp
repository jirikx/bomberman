#include "LeaderBoard.hpp"
#include <fstream>
#include <map>
#include <algorithm>

LeaderBoard::LeaderBoard(const std::string &pathToLeaderBoard)
  : SceneManager(getmaxy(stdscr), getmaxx(stdscr)), m_PathToLeaderBoard(pathToLeaderBoard) {}

void LeaderBoard::write(const std::pair<std::string, size_t> &result) {
    std::ofstream fileStream;
    fileStream.open(m_PathToLeaderBoard, std::ios_base::app);

    if (!fileStream)
        throw std::runtime_error("Can't open file!");

    fileStream << result.first << "=" << result.second << std::endl;
}

void LeaderBoard::print(int maxRows) {
    int startColumn;
    std::vector<std::pair<std::string, size_t>> results = getResults();
    initScene();

    int rows = std::min({m_Height, maxRows, int(results.size())});
    for (int i = 0; i < rows; i++) {
        std::string text = std::to_string(i + 1) + ". " + results[i].first + ", score: " + std::to_string(results[i].second);
        int len = int(text.length());
        if (len > m_Width) {
            text = text.substr(0, m_Width);
            startColumn = 0;
        } else {
            startColumn = (m_Width - len) / 2;
        }
        printStringAt({startColumn, i}, text);
    }

    wgetch(m_Window);
}

std::vector<std::pair<std::string, size_t>> LeaderBoard::getResults() {
    std::map<std::string, size_t> playersScores;
    std::ifstream fileStream;
    fileStream.open(m_PathToLeaderBoard);

    if (!fileStream)
        throw std::runtime_error("Can't open file!");

    // Load all results from the file stream
    std::string nickname, definition;
    size_t score;
    while (std::getline(fileStream, nickname, '=')) {
        if (!std::getline(fileStream, definition))
            throw std::logic_error("Missing definition inside leader board!");
        if (definition[0] == '-')
            throw std::logic_error("Negative score value inside leader board!");

        try {
            score = std::stoul(definition);
        } catch (std::exception &exc) {
            throw std::logic_error("Wrong score value inside leader board!");
        }

        auto playerIt = playersScores.find(nickname);
        if (playerIt == playersScores.end())
            playersScores[nickname] = score;
        else
            playerIt->second += score;
    }

    // Convert the map to vector which is sorted by highest score
    std::vector<std::pair<std::string, size_t>> results(playersScores.begin(), playersScores.end());
    std::sort(results.begin(), results.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second > rhs.second;
    });

    return results;
}
