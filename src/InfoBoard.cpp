#include "InfoBoard.hpp"
#include <iostream>

InfoBoard::InfoBoard(int height, int width, int startY, int startX)
  : SceneManager(height, width, startY, startX) {}

void InfoBoard::setup() {
    initScene();
    box(m_Window, 0, 0);
    wrefresh(m_Window);
    refresh();
}

void InfoBoard::printNowPlaying(const std::shared_ptr<AbstractPlayer> &player) {
    printStringAt({1, 1}, "Now playing: " + player->m_NickName + " (" + player->m_Texture + ")");
    box(m_Window, 0, 0);
    refreshScene();
}

void InfoBoard::printLastBonus(const std::string &bonusName) {
    printStringAt({1, 2}, "Last bonus: " + bonusName);
    box(m_Window, 0, 0);
    refreshScene();
}

void InfoBoard::clearLastBonus() {
    clearLine(2);
    box(m_Window, 0, 0);
}
