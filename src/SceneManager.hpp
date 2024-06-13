#pragma once
#include <ncurses.h>
#include "Coords.hpp"

class SceneManager {
public:
    SceneManager(int height, int width, int startY = 0, int startX = 0);

    SceneManager(const SceneManager &rhs);

    SceneManager& operator=(const SceneManager &rhs) = delete;

    virtual ~SceneManager();

    void refreshScene();

    void clearScene();

    bool clearAt(const Coords &coords);

    bool printAt(const Coords &coords, char texture);

    bool printStringAt(const Coords &coords, const std::string &text);

    void clearLine(int y);

    int getHeight() const;

    int getWidth() const;

    int getY() const;

    int getX() const;

protected:
    void initScene();

    bool isInside(const Coords &coords) const;

    const int m_Height, m_Width;
    int m_Y, m_X;
    WINDOW * m_Window;
};
