#include "Application.hpp"
#include "LeaderBoard.hpp"

Application::Application(const Configuration &config, const LeaderBoard &leaderBoard)
  : m_Game(config.getGameBoard(), config.getAllPlayers(), config.getBonusChances()),
    m_IsRunning(false), m_Config(config), m_LeaderBoard(leaderBoard) {}

Application::~Application() = default;

void Application::run() {
    m_Game.start();

    m_IsRunning = true;
    while (m_IsRunning) {
        m_Game.render();
        m_IsRunning = m_Game.update();
    }

    handleWinners();
}

void Application::handleWinners() {
    auto winners = m_Game.getWinners();

    // Show info about winner(s)
    std::string winnerMessage;
    if (winners.empty() || winners[0].second == 0)
        winnerMessage = "Nobody won";
    else if (winners.size() == 1)
        winnerMessage = "Winner: " + winners[0].first + ", score: " + std::to_string(winners[0].second);
    else
        winnerMessage = "Draw";
    printw("%s", winnerMessage.c_str());
    getch();

    // Write winner info into the leaderboard
    for (auto &w : winners)
        if (w.second != 0)
            m_LeaderBoard.write(w);
}
