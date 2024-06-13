#include "Configuration.hpp"
#include <sstream>
#include <algorithm>
#include <list>
#include "ncurses.h"
#include <iostream>

const std::map<std::string, int> Configuration::m_SpecialKeys = {
    {"KEY_UP", KEY_UP},
    {"KEY_DOWN", KEY_DOWN},
    {"KEY_LEFT", KEY_LEFT},
    {"KEY_RIGHT", KEY_RIGHT}
};

Configuration::Configuration(const std::string &path) {
    srand(time(nullptr));
    parseGameConfig(path);
}

std::shared_ptr<GameBoard> Configuration::getGameBoard() const {
    return m_GameBoard;
}

std::vector<std::shared_ptr<AbstractPlayer>> Configuration::getAllPlayers() const {
    std::vector<std::shared_ptr<AbstractPlayer>> res = m_GameBoardBuilder.getComputerPlayers();
    res.insert(res.end(), m_HumanPlayers.begin(), m_HumanPlayers.end());

    return res;
}

std::vector<std::pair<int, std::shared_ptr<Bonus>>> Configuration::getBonusChances() const {
    return m_BonusChances;
}

void Configuration::parseGameConfig(const std::string &fileName) {
    std::ifstream configFile(fileName, std::ios_base::in);
    std::string line;

    if (!configFile)
        throw std::runtime_error("Config file " + fileName + " couldn't be opened!");

    // Parse any number of human players
    while (std::getline(configFile, line)) {
        if (line.length() >= 8 && line.substr(0,7) == "[player" && line.back() == ']')
            parsePlayer(configFile);
        else
            break;
        std::getline(configFile, line);
    }
    if (m_HumanPlayers.empty())
        throw ConfigParseException("No human players in the config file!");

    // Parse the bonuses
    if (line == "[bonus_chance]")
        parseBonuses(configFile);
    else
        throw ConfigParseException("Missing bonus_chance definition in the config file! Instead got: " + line);

    // Parse the game board
    std::getline(configFile, line);
    if (line == "[game_board]")
        parseGameBoard(configFile);
    else
        throw ConfigParseException("Missing game_board definition in the config file!");
}

void Configuration::parsePlayer(std::ifstream &configFile) {
    PlayerStats stats;
    std::map<int, EAction> controls;

    std::string texture = parseOneDefinition(configFile, "texture");
    if (texture.length() != 1)
        throw ConfigParseException("Wrong player texture definition!");

    std::string nickname = parseOneDefinition(configFile, "nickname");
    parsePlayerStats(configFile, stats);
    parseControls(configFile, controls);

    // Create parsed player
    m_HumanPlayers.emplace_back(new PlayerHuman(stats, {0, 0}, texture[0], nickname, controls));
}

void Configuration::parsePlayerStats(std::ifstream &configFile, PlayerStats &playerStats) {
    playerStats.hp = stringToInt(parseOneDefinition(configFile, "hp"));
    playerStats.freeBombs = stringToInt(parseOneDefinition(configFile, "free_bombs"));
    playerStats.wallJumpCount = stringToInt(parseOneDefinition(configFile, "wall_jump_count"));

    std::string _hasImmunity = parseOneDefinition(configFile, "has_immunity");
    if (_hasImmunity == "false")
        playerStats.hasImmunity = false;
    else if (_hasImmunity == "true")
        playerStats.hasImmunity = true;
    else
        throw ConfigParseException("Wrong definition for the key: has_immunity");

    playerStats.bombRange = stringToInt(parseOneDefinition(configFile, "bomb_range"));
}

void Configuration::parseControls(std::ifstream &configFile, std::map<int, EAction> &playerControls) {
    parseSingleControl(configFile, playerControls, "move_up");
    parseSingleControl(configFile, playerControls, "move_down");
    parseSingleControl(configFile, playerControls, "move_left");
    parseSingleControl(configFile, playerControls, "move_right");
    parseSingleControl(configFile, playerControls, "plant_bomb");

    // Add option to quit the game
    playerControls.insert({int('q'), EAction::QUIT_GAME});
}

void Configuration::parseSingleControl(std::ifstream &configFile, std::map<int, EAction> &playerControls, const std::string &move) {
    std::string playerKey = parseOneDefinition(configFile, move);
    EAction action = stringToAction(move);

    if (playerKey.length() == 1) {
        if (!playerControls.insert({int(playerKey[0]), action}).second)
            throw ConfigParseException("Key-collision inside keyboard settings in the config!");
    } else {
        auto it = m_SpecialKeys.find(playerKey);
        if (it == m_SpecialKeys.end() || !playerControls.insert({it->second, action}).second)
            throw ConfigParseException("Wrong keyboard setting in the config!");
    }
}

void Configuration::parseBonuses(std::ifstream &configFile) {
    std::string line;
    std::set<std::string> usedBonuses;

    // Loop through all the bonus definitions in the config file
    while (std::getline(configFile, line)) {
        if (line.empty())
            return;

        std::pair<std::string, std::string> definition;
        std::istringstream iss(line);
        if (!std::getline(iss, definition.first, '=') || !std::getline(iss, definition.second))
            throw ConfigParseException("Missing key/value in the bonus definition!");
        if (!usedBonuses.insert(definition.first).second)
            throw ConfigParseException("Redefinition of the same bonus in the config file is forbidden!");

        parseSingleBonus(definition.first, definition.second);
    }

    // Sort parsed bonuses by their chances
    std::sort(m_BonusChances.begin(), m_BonusChances.end(), [](auto &lhs, auto &rhs) {
        return lhs.first < rhs.first;
    });
}

void Configuration::parseSingleBonus(const std::string &name, const std::string &_chance) {
    std::shared_ptr<Bonus> bonus;
    int chance;

    // Validate bonus chance
    try {
        chance = stringToInt(_chance);
    } catch (std::exception &exc) {
        throw ConfigParseException("Wrong bonus definition in the config!");
    }
    if (chance < 0 || chance > 100)
        throw ConfigParseException("Bonus chance is out of allowed range!");

    if (name == "wall_jump")
        bonus = std::make_shared<BonusWallJump>();
    else if (name == "extra_bombs")
        bonus = std::make_shared<BonusExtraBombs>();
    else if (name == "extra_hp")
        bonus = std::make_shared<BonusExtraHp>();
    else if (name == "strong_bomb")
        bonus = std::make_shared<BonusStrongBomb>();
    else if (name == "immunity")
        bonus = std::make_shared<BonusImmunity>();
    else
        throw ConfigParseException("Unknown bonus name in the config!");

    m_BonusChances.emplace_back(chance, bonus);
}

void Configuration::parseGameBoard(std::ifstream &configFile) {
    if (!m_GameBoardBuilder.prepareGameBoard(configFile, m_HumanPlayers))
        throw ConfigParseException("Wrong game board in the config!");

    m_GameBoard = m_GameBoardBuilder.createGameBoard();
    for (auto &p : m_HumanPlayers)
        p->m_GameBoard = m_GameBoard;
}

std::string Configuration::parseOneDefinition(std::ifstream &configFile, const std::string &expectedKey) {
    std::string name, definition;

    if (!std::getline(configFile, name, '=') || name != expectedKey || !std::getline(configFile, definition))
        throw ConfigParseException("Wrong key/value definition inside config file! Expected key: " + expectedKey);

    return definition;
}

int Configuration::stringToInt(const std::string &_value) {
    int value;

    if (!allDigits(_value))
        throw ConfigParseException("Can't convert to int from: " + _value);
    try {
        value = std::stoi(_value);
    } catch (std::exception &exc) {
        throw ConfigParseException("Can't convert to int from: " + _value);
    }

    return value;
}

bool Configuration::allDigits(const std::string &value) {
    return std::all_of(value.begin(), value.end(), [](char c) {
        return isdigit(c);
    });
}