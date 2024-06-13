#include "EAction.hpp"
#include <stdexcept>

EAction stringToAction(const std::string &action) {
    auto it = actionTable.find(action);
    if (it == actionTable.end())
        throw std::logic_error("String " + action + " couldn't be converted to EAction!");

    return it->second;
}

std::string actionToString(EAction action) {
    for (auto &p : actionTable)
        if (p.second == action)
            return p.first;

    throw std::logic_error("Action couldn't be converted to string!");
}
