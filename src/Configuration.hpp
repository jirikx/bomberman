#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include "PlayerHuman.hpp"
#include "PlayerComputer.hpp"
#include "GameBoardBuilder.hpp"
#include "BonusExtraBombs.hpp"
#include "BonusExtraHp.hpp"
#include "BonusImmunity.hpp"
#include "BonusStrongBomb.hpp"
#include "BonusWallJump.hpp"
#include "ConfigParseException.hpp"

/**
 * @brief Class for parsing game configuration
 *
 */
class Configuration {
public:
    /**
     * @brief Constructor
     *
     * @param path to the config file
     */
    explicit Configuration(const std::string &path);

    /**
     * @brief Returns previously created GameBoard
     *
     * @return shared pointer with GameBoard instance
     */
    std::shared_ptr<GameBoard> getGameBoard() const;

    /**
     * @brief Returns previously created players
     *
     * Players can be of various types
     * @return vector of shared pointers with players
     */
    std::vector<std::shared_ptr<AbstractPlayer>> getAllPlayers() const;

    /**
     * @brief Returns bonuses with their chances to be applied
     *
     * @return vector of shared pointers with bonuses
     */
    std::vector<std::pair<int, std::shared_ptr<Bonus>>> getBonusChances() const;

private:
    /**
     * @brief Starts parsing of the whole game config file
     *
     * @param fileName path to the file with the config
     */
    void parseGameConfig(const std::string &fileName);

    /**
     * @brief Parses one player from the config file
     *
     * @param configFile config file stream
     */
    void parsePlayer(std::ifstream &configFile);

    /**
     * @brief Parses the stats of one player
     *
     * @param configFile config file stream
     * @param playerStats output parameter
     */
    void parsePlayerStats(std::ifstream &configFile, PlayerStats &playerStats);

    /**
     * @brief Parses player controls which are present on PlayerHuman
     *
     * @param configFile config file stream
     * @param playerControls output parameter
     */
    void parseControls(std::ifstream &configFile, std::map<int, EAction> &playerControls);

    /**
     * @brief Parses one key and definition of the player controls
     *
     * @param configFile config file stream
     * @param playerControls output parameter
     * @param move name of the action
     */
    void parseSingleControl(std::ifstream &configFile, std::map<int, EAction> &playerControls, const std::string &move);

    /**
     * @brief Parses all bonuses and their chances
     * If some known bonus isn't in the config, we assume that its chance is 0
     *
     * @param configFile config file stream
     */
    void parseBonuses(std::ifstream &configFile);

    /**
     * @brief Parses one bonus-chance pair
     *
     * @param name of the bonus
     * @param chance of the bonus (probability in %)
     */
    void parseSingleBonus(const std::string &name, const std::string &chance);

    /**
     * @brief Parses the whole game board
     *
     * This method parses the map, type of walls, and players locations
     * @param configFile config file stream
     */
    void parseGameBoard(std::ifstream &configFile);

    /**
     * @brief Parses one definition which is assigned to given key
     *
     * @param configFile config file stream
     * @param expectedKey is a key which should be on the current line in the config file
     * @return the definition
     */
    static std::string parseOneDefinition(std::ifstream &configFile, const std::string &expectedKey);

    /**
     * @brief Tries to convert string to integer
     *
     * @param _value string to convert
     * @return parsed integer
     */
    static int stringToInt(const std::string &_value);

    /**
     * @brief Checks if all characters are digits
     *
     * @param value string to check
     * @return true if all the characters are digits, false otherwise
     */
    static bool allDigits(const std::string &value);

    /**
     * @brief Contains all control keys which aren't just regular characters
     * For example the arrow keys on the keyboard
     */
    static const std::map<std::string, int> m_SpecialKeys;

    std::vector<std::shared_ptr<PlayerHuman>> m_HumanPlayers;
    std::vector<std::shared_ptr<AbstractPlayer>> m_ComputerPlayers;
    std::vector<std::pair<int, std::shared_ptr<Bonus>>> m_BonusChances;
    GameBoardBuilder m_GameBoardBuilder;
    std::shared_ptr<GameBoard> m_GameBoard;
};