#include "Game.hpp"
#include <iostream>
#include <algorithm>

Game::Game(const std::shared_ptr<GameBoard> &gameBoard, const std::vector<std::shared_ptr<AbstractPlayer>> &players,
           const std::vector<std::pair<int, std::shared_ptr<Bonus>>> &bonusChances)
  : m_GameBoard(gameBoard),
    m_InfoBoard(new InfoBoard(5, gameBoard->getWidth(),
                                gameBoard->getY() + gameBoard->getHeight(), gameBoard->getX())),
    m_Players(players), m_BonusChances(bonusChances) {
    size_t idCount = 0;
    for (auto &player : players)
        player->m_Id = idCount++;
}

void Game::start() {
    m_GameBoard->setup();
    m_InfoBoard->setup();

    for (auto &player : m_Players)
        m_GameBoard->printAt(player->m_Coords, player->m_Texture);
}

void Game::render() {
    m_GameBoard->printTiles();
}

bool Game::update() {
    if (!updatePlayers())
        return false;

    // Update bomb ticks and try to apply bonuses
    auto playerBonuses = m_GameBoard->updateBombs();
    for (auto &pb : playerBonuses)
        if (pb.second > 0) {
            tryGetBonus(m_Players[pb.first], pb.second);
        }

    // Update flame ticks
    m_GameBoard->updateFlames();

    // Redraw all players
    for (auto &player : m_Players)
        if (player->isAlive())
            m_GameBoard->printAt(player->m_Coords, player->m_Texture);

    return true;
}

std::vector<std::pair<std::string, size_t>> Game::getWinners() const {
    std::vector<std::pair<std::string, size_t>> winners;
    for (auto &p : m_Players)
        if (p->participatesInLeaderboard() && p->isAlive())
            winners.emplace_back(p->m_NickName, p->m_Score);

    if (winners.empty())
        return winners;

    std::sort(winners.begin(), winners.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second > rhs.second;
    });

    // Keep only the players with the highest score
    size_t maxScore = winners[0].second;
    for (auto it = winners.begin(); it != winners.end(); it++)
        if (it->second < maxScore) {
            winners.erase(it, winners.end());
            break;
        }

    return  winners;
}

bool Game::updatePlayers() {
    size_t alivePlayers = 0;
    size_t playersWithScore = 0;

    for (auto &player : m_Players) {
        if (!player->isAlive())
            continue;
        alivePlayers++;

        if (player->participatesInLeaderboard())
            playersWithScore++;
        m_InfoBoard->printNowPlaying(player);

        // Do the action specified by player
        EAction action = player->updateAction();
        if (action == EAction::QUIT_GAME)
            return false;
        else if (action == EAction::PLANT_BOMB)
            handleBombPlant(player);
        else
            handleMovement(player, action);

        // Print the player and info about his last bonus
        m_GameBoard->printAt(player->m_Coords, player->m_Texture);
        auto it = m_LastPlayerBonus.find(player);
        if (it != m_LastPlayerBonus.end()) {
            m_InfoBoard->clearLastBonus();
            m_InfoBoard->printLastBonus(it->second->getName());
        }

        checkDeadlyCollisions(player);
    }

    // The game is finished when there is only one survivor or when all the players who count their score died
    if (alivePlayers == 1 || !playersWithScore)
        return false;

    return true;
}

void Game::handleBombPlant(const std::shared_ptr<AbstractPlayer> &player) {
    // Only the player on correct position with some free bombs can plant the bomb
    if (player->m_Stats.freeBombs > 0 && m_GameBoard->canMoveTo(player->m_Coords)) {
        m_GameBoard->addBomb(Bomb(player->m_Coords, player->m_Id, DEFAULT_BOMB_TIME, player->m_Stats.bombRange));
        player->m_Stats.freeBombs--;
    }
}

void Game::handleMovement(const std::shared_ptr<AbstractPlayer> &player, EAction action) {
    Coords newCoords = player->m_Coords + action;

    if (m_GameBoard->canMoveTo(newCoords)) {
        m_GameBoard->clearAt(player->m_Coords);
        player->m_Coords = newCoords;
    } else if (player->m_Stats.wallJumpCount > 0 && m_GameBoard->canMoveTo(newCoords + action)) {
        // If the player can jump over the wall, we let him do it
        m_GameBoard->clearAt(player->m_Coords);
        player->m_Stats.wallJumpCount--;
        player->m_Coords = newCoords + action;
    }
}

void Game::tryGetBonus(const std::shared_ptr<AbstractPlayer> &player, size_t tries) {
    // Logic to try to get bonuses
    for (size_t i = 0; i < tries; i++) {
        int randomNumber = rand() % 100;
        for (auto &bc : m_BonusChances)
            if (randomNumber < bc.first) {
                bc.second->activateBonus(player->m_Stats);
                m_LastPlayerBonus[player] = bc.second;
                return;
            }
    }
}

void Game::checkDeadlyCollisions(const std::shared_ptr<AbstractPlayer> &player) {
    auto flame = m_GameBoard->getFlameAt(player->m_Coords);

    // Check if the player was killed by a hit
    if (flame.has_value()) {
        auto enemy = m_Players.at(flame.value().m_OwnerId);
        if (!player->isImmuneAgainst(enemy) && player->getHit(DEFAULT_DAMAGE)) {
            if (player->m_Id != enemy->m_Id)
                enemy->m_Score += KILL_POINTS;
            return;
        }
    }

    // Check collisions with other players (only when the player survived)
    for (auto &p : m_Players)
        if (p->m_Id != player->m_Id && p->m_Coords == player->m_Coords && p->getHit(DEFAULT_DAMAGE)) {
            player->m_Score += KILL_POINTS;
        }
}
