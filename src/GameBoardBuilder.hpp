#pragma once
#include "GameBoard.hpp"
#include "PlayerComputer.hpp"
#include "PlayerHuman.hpp"

const int COMP_PLAYER_HP = 1;
const int COMP_PLAYER_BOMBS = 0;
const char COMP_PLAYER_TEXTURE = 'B';

/**
 * @brief Class which is used for creating GameBoard from the config
 */
class GameBoardBuilder {
public:
    GameBoardBuilder();

    /**
     * @brief Parses data for GameBoard creation from the config file
     *
     * @param configFile config file stream
     * @param humanPlayers vector of PlayerHuman, every player will get its starting coordinates
     *                     based on the info from GameBoard
     * @return true if the GameBoard was successfully parsed, false otherwise
     */
    bool prepareGameBoard(std::ifstream &configFile, std::vector<std::shared_ptr<PlayerHuman>> &humanPlayers);

    /**
     * @brief Creates new GameBoard from previously parsed data
     *
     * @return the GameBoard
     */
    std::shared_ptr<GameBoard> createGameBoard() const;

    std::vector<std::shared_ptr<AbstractPlayer>> getComputerPlayers() const;

private:
    void addWallAt(const Coords &coords, bool destructible);

    int m_Height, m_Width;
    std::map<Coords, bool> m_Walls;
    std::vector<std::shared_ptr<AbstractPlayer>> m_ComputerPlayers;
};