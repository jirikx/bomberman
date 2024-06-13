#include "InputHandler.hpp"

const std::string InputHandler::DEFAULT_CONFIG_PATH = "./examples/levels/config.ini";
const std::string InputHandler::DEFAULT_LEADERBOARD_PATH = "./examples/leaderboard";

InputHandler::InputHandler() {
    initscr();
    curs_set(0);
    noecho();
    raw();
    refresh();
}

InputHandler::~InputHandler() {
    endwin();
}

void InputHandler::init(int argc, char **argv) const {
    if (argc == 1) {
        startApplication(DEFAULT_CONFIG_PATH, DEFAULT_LEADERBOARD_PATH);
    } else if (argc == 2) {
        std::string argument(argv[1]);
        if (argument == "--leaderboard")
            showLeaderBoard(DEFAULT_LEADERBOARD_PATH);
        else
            startApplication(argument, DEFAULT_LEADERBOARD_PATH);
    } else {
        throw std::invalid_argument("Wrong program arguments! Possible usage: " + std::string(argv[0]) + " <optional_path_to_config>");
    }
}

void InputHandler::startApplication(const std::string &configPath, const std::string &leaderBoardPath) const {
    Configuration config(configPath);
    LeaderBoard leaderBoard(DEFAULT_LEADERBOARD_PATH);
    Application app(config, leaderBoard);
    app.run();
}

void InputHandler::showLeaderBoard(const std::string &path) const {
    LeaderBoard leaderBoard(path);
    leaderBoard.print();
}
