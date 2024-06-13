#include <ncurses.h>
#include <exception>
#include <iostream>
#include "InputHandler.hpp"

int main(int argc, char ** argv) {
    try {
        InputHandler inputHandler;
        inputHandler.init(argc, argv);
    } catch (std::exception &exc) {
        std::cout << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}