#include "GameBoardBuilder.hpp"
#include <list>
#include <algorithm>
#include <fstream>
#include <random>
#include <set>
#include <iostream>

GameBoardBuilder::GameBoardBuilder()
  : m_Height(0), m_Width(0) {}

bool GameBoardBuilder::prepareGameBoard(std::ifstream &configFile, std::vector<std::shared_ptr<PlayerHuman>> &humanPlayers) {
    std::list<std::string> gameBoardRows;
    std::string line;
    std::set<char> usedPlayerTextures;

    // Initialize the enemy for computer players
    std::shared_ptr<AbstractPlayer> enemyPlayer;
    if (humanPlayers.empty())
        enemyPlayer = nullptr;
    else
        enemyPlayer = humanPlayers[rand() % humanPlayers.size()];

    // Calculate height of the game board
    while (std::getline(configFile, line)) {
        gameBoardRows.push_back(line);
        m_Height++;
    }

    // Map must have at least 3 rows and 3 columns  (2 are for borders, 1 for playing space)
    m_Width = int(gameBoardRows.front().size());
    if (m_Height < 3 || m_Width < 3)
        return false;

    // Check upper border of the map
    if (std::any_of(gameBoardRows.front().begin(), gameBoardRows.front().end(), [] (char c) {
            return c != WALL_SOLID;
        }))
        return false;

    // Check lower border of the map
    if (int(gameBoardRows.back().size()) != m_Width ||
        std::any_of(gameBoardRows.back().begin(), gameBoardRows.back().end(), [] (char c) {
            return c != WALL_SOLID;
        }))
        return false;

    // Create game board from the rest of the map
    int rowIndex = 0;
    for (auto &row : gameBoardRows) {
        if (int(row.size()) != m_Width || row[0] != WALL_SOLID || row[row.size() - 1] != WALL_SOLID)
            return false;

        // Create game objects from the game board
        for (int i = 0; i < int(row.size()); i++) {
            if (row[i] == TILE_EMPTY)
                continue;
            else if (row[i] == WALL_SOLID)
                addWallAt({i, rowIndex}, false);
            else if (row[i] == WALL_DESTRUCTIBLE)
                addWallAt({i, rowIndex}, true);
            else if (row[i] == COMP_PLAYER_TEXTURE)
                m_ComputerPlayers.emplace_back(new PlayerComputer(COMP_PLAYER_HP, COMP_PLAYER_BOMBS, {i, rowIndex}, enemyPlayer));
            else {
                bool isPlayerTexture = false;
                for (auto &p : humanPlayers)
                    if (p->m_Texture == row[i]) {
                        if (!usedPlayerTextures.insert(p->m_Texture).second)
                            return false;
                        p->m_Coords = {i, rowIndex};
                        isPlayerTexture = true;
                        break;
                    }
                if (!isPlayerTexture)
                    return false;
            }
        }
        rowIndex++;
    }

    return humanPlayers.size() == usedPlayerTextures.size();
}

void GameBoardBuilder::addWallAt(const Coords &coords, bool destructible) {
    m_Walls.insert({coords, destructible});
}

std::shared_ptr<GameBoard> GameBoardBuilder::createGameBoard() const {
    return std::make_shared<GameBoard>(m_Height, m_Width, m_Walls);
}

std::vector<std::shared_ptr<AbstractPlayer>> GameBoardBuilder::getComputerPlayers() const {
    return m_ComputerPlayers;
}
