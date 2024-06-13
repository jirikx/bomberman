#pragma once
#include <string>
#include <unordered_map>

/**
 * @brief Enumerates possible actions which can be done by the player
 *
 */
enum class EAction {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    PLANT_BOMB,
    QUIT_GAME,
    DO_NOTHING
};

inline const std::unordered_map<std::string, EAction> actionTable = {
    {"move_up", EAction::MOVE_UP},
    {"move_down", EAction::MOVE_DOWN},
    {"move_left", EAction::MOVE_LEFT},
    {"move_right", EAction::MOVE_RIGHT},
    {"plant_bomb", EAction::PLANT_BOMB},
    {"quit_game", EAction::QUIT_GAME},
    {"do_nothing", EAction::DO_NOTHING}
};

/**
 * @brief Converts string to the action
 *
 * If the string doesn't name any action, then an exception is thrown
 * @param action to be converted
 * @return action from string
 */
EAction stringToAction(const std::string &action);

/**
 * @brief Opposite function to the stringToAction
 *
 * @param action to be converted
 * @return string from action
 */
std::string actionToString(EAction action);