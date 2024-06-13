#include "SceneManager.hpp"
#include <stdexcept>
#include <iostream>

SceneManager::SceneManager(int height, int width, int startY, int startX)
  : m_Height(height), m_Width(width), m_Y(startY), m_X(startX), m_Window(nullptr) {}

SceneManager::SceneManager(const SceneManager &rhs)
  : m_Height(rhs.m_Height), m_Width(rhs.m_Width), m_Y(rhs.m_Y), m_X(rhs.m_X), m_Window(nullptr) {}

SceneManager::~SceneManager() {
    if (m_Window)
        delwin(m_Window);
}

void SceneManager::initScene() {
    m_Window = newwin(m_Height, m_Width, m_Y, m_X);
    if (!m_Window)
        throw std::logic_error("Couldn't initialize ncurses window");
    wrefresh(m_Window);
    refresh();
}

void SceneManager::refreshScene() {
    wrefresh(m_Window);
}

bool SceneManager::clearAt(const Coords &coords) {
    return printAt(coords, ' ');
}

bool SceneManager::printAt(const Coords &coords, char texture) {
    if (!isInside(coords))
        return false;

    mvwaddch(m_Window, coords.y, coords.x, texture);
    return true;
}

void SceneManager::clearScene() {
    wclear(m_Window);
}

bool SceneManager::printStringAt(const Coords &coords, const std::string &text) {
    if (!isInside(coords))
        return false;

    std::string toPrint = text;
    auto terminalWidth = size_t(m_Width);
    if (text.size() > terminalWidth)
        toPrint = text.substr(0, terminalWidth);

    clearLine(coords.y);
    mvwprintw(m_Window, coords.y, coords.x, "%s", toPrint.c_str());
    wrefresh(m_Window);
    return true;
}

void SceneManager::clearLine(int y) {
    wmove(m_Window, y, 0);
    wclrtoeol(m_Window);
}

int SceneManager::getHeight() const {
    return m_Height;
}

int SceneManager::getWidth() const {
    return m_Width;
}

int SceneManager::getY() const {
    return m_Y;
}

int SceneManager::getX() const {
    return m_X;
}

bool SceneManager::isInside(const Coords &coords) const {
    return coords.x >= 0 && coords.x < m_Width && coords.y >= 0 && coords.y < m_Width;
}