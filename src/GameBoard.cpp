#include "GameBoard.hpp"
#include <stdexcept>
#include <iostream>

GameBoard::GameBoard(int height, int width, const std::map<Coords, bool> &walls)
  : SceneManager(height, width, getmaxy(stdscr)/2 - height/2, getmaxx(stdscr)/2 - width/2),
    m_Walls(walls) {}

GameBoard::GameBoard(int height, int width)
  : GameBoard(height, width, std::map<Coords, bool>()) {}

void GameBoard::setup() {
    initScene();
    notimeout(m_Window, true);
    keypad(m_Window, true);
    wrefresh(m_Window);
    refresh();
}

void GameBoard::printTiles() {
    // Print walls
    for (auto &w : m_Walls) {
        char texture = WALL_SOLID;
        if (w.second)
            texture = WALL_DESTRUCTIBLE;
        printAt(w.first, texture);
    }

    // Print bombs
    for (auto &b : m_Bombs)
        printAt(b.first, b.second.m_Texture);

    // Print flames
    for (auto &f : m_Flames)
        printAt(f.first, f.second.m_Texture);

    wrefresh(m_Window);
    refresh();
}

EAction GameBoard::getAction(const std::map<int, EAction> &controls) const {
    int userInput = wgetch(m_Window);
    auto action = controls.find(userInput);

    if (action == controls.end())
        return EAction::DO_NOTHING;

    return action->second;
}

bool GameBoard::canMoveTo(const Coords &coords) const {
    return m_Walls.find(coords) == m_Walls.end() && m_Bombs.find(coords) == m_Bombs.end()
           && isInside(coords);
}

bool GameBoard::addBomb(const Bomb &bomb) {
    return m_Bombs.insert({bomb.getCoords(), bomb}).second;
}

std::map<size_t, size_t> GameBoard::updateBombs() {
    std::map<size_t, size_t> playerToBonus;

    auto bomb = m_Bombs.begin();
    while (bomb != m_Bombs.end()) {
        size_t possibleBonuses = 0;
        bomb->second.update();

        // Check if the bomb should explode in this round
        if (bomb->second.shouldExplode()) {
            possibleBonuses = generateFlames(bomb->second);

            // Give possible bonuses to the player
            if (possibleBonuses > 0) {
                auto it = playerToBonus.find(bomb->second.m_OwnerId);
                if (it == playerToBonus.end())
                    playerToBonus.insert({bomb->second.m_OwnerId, possibleBonuses});
                else
                    it->second += possibleBonuses;
            }
            bomb = m_Bombs.erase(bomb);
        } else {
            ++bomb;
        }
    }

    return playerToBonus;
}

void GameBoard::updateFlames() {
    auto flame = m_Flames.begin();
    while (flame != m_Flames.end()) {
        if (!flame->second.update()) {
            clearAt(flame->second.m_Coords);
            flame = m_Flames.erase(flame);
        } else {
            ++flame;
        }
    }
}

std::optional<Flame> GameBoard::getFlameAt(const Coords &coords) const {
    auto it = m_Flames.find(coords);
    if (it != m_Flames.end())
        return it->second;

    return {};
}

bool GameBoard::addFlame(const Flame &flame) {
    clearAt(flame.m_Coords);
    printAt(flame.m_Coords, flame.m_Texture);
    return m_Flames.insert({flame.getCoords(), flame}).second;
}

size_t GameBoard::generateFlames(const Bomb &bomb) {
    size_t bonusGeneratingCount = 0;

    addFlame(Flame(bomb.m_Coords, bomb.m_OwnerId, EXPLOSION_DURATION));
    bonusGeneratingCount += createFlamesInDirection(bomb, 0, 1);
    bonusGeneratingCount += createFlamesInDirection(bomb, 0, -1);
    bonusGeneratingCount += createFlamesInDirection(bomb, 1, 0);
    bonusGeneratingCount += createFlamesInDirection(bomb, -1, 0);

    return bonusGeneratingCount;
}

size_t GameBoard::createFlamesInDirection(const Bomb &bomb, int x, int y) {
    size_t bonusGeneratingCount = 0;

    for (int i = 1; i <= bomb.m_Range; i++) {
        Coords coord = bomb.m_Coords + Coords(x*i, y*i);
        if (m_Flames.find(coord) != m_Flames.end())
            continue;

        auto wall = m_Walls.find(coord);

        // If there wasn't any solid wall, the flame will spread there
        if (isInside(coord) && (wall == m_Walls.end() || wall->second))
            addFlame(Flame(coord, bomb.m_OwnerId, EXPLOSION_DURATION));

        // If the flame hit a solid wall, it can't spread in this direction
        if (wall != m_Walls.end() && !wall->second)
            break;

        // If the wall was destructible, the flame will erase it
        if (wall != m_Walls.end() && wall->second) {
            m_Walls.erase(wall);
            bonusGeneratingCount++;
        }
    }

    return bonusGeneratingCount;
}
