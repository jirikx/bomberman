#include "../src/PlayerHuman.hpp"
#include "../src/BonusExtraBombs.hpp"
#include "../src/Configuration.hpp"
#include <cassert>
#include <memory>
#include <map>
#include <iostream>

void testPlayer() {
    std::map<int, EAction> playerControls;
    auto playerHuman = std::make_shared<PlayerHuman>(1, 0, "Player1", Coords(1, 1), playerControls);
    auto bonusExtraBombs = std::make_shared<BonusExtraBombs>(42);
    auto bonusMinusBombs = std::make_shared<BonusExtraBombs>(-41);

    bonusExtraBombs->activateBonus(playerHuman->m_Stats);
    assert(playerHuman->m_Stats.freeBombs == 42);

    bonusMinusBombs->activateBonus(playerHuman->m_Stats);
    assert(playerHuman->m_Stats.freeBombs == 1);

    assert(playerHuman->getHit(1));
    assert(!playerHuman->getHit(1));

    assert(!playerHuman->isAlive());
}

bool testNonExistingFile() {
    const char charPool[] = "abcdefghijklmnopqrstuvwxyz89442144AncAcjnfa";
    size_t pathLen = rand() % 50;
    std::string randomStr;
    randomStr.reserve(pathLen);

    for (size_t i = 0; i < pathLen; i++)
        randomStr += charPool[rand() % (sizeof(charPool) - 1)];

    try {
        Configuration config(randomStr);
    } catch (std::runtime_error &exc) {
        return true;
    }

    return false;
}

bool testUnsuccessfulParse(const std::string &path) {
    try {
        Configuration config(path);
    } catch (ConfigParseException &exc) {
        return true;
    }

    return false;
}

bool testMultipleConfigs() {
    std::string prefix = "tests/";
    std::vector<std::string> paths = {
        "missing_map.ini",
        "empty_file.ini",
        "missing_bonus.ini",
        "missing_controls.ini",
        "two_same_players.ini",
        "two_same_textures.ini"
    };

    for (auto &p : paths)
        if (!testUnsuccessfulParse(prefix + p))
            return false;

    return true;
}

int main() {
    srand(time(nullptr));

    testPlayer();
    assert(testMultipleConfigs());
    assert(testNonExistingFile());

    std::cout << "Tests passed!" << std::endl;
}