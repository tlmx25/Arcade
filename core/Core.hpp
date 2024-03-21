/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#pragma once

#include <iostream>
#include <memory>
#include "Object.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include "CLibEncapsulation.hpp"

/**
 * @file Core.hpp
 * @brief Core class for the Arcade project
 **/

/**
* @class Core
 * @brief A class to represent the core of the Arcade project, manage the game and the display.
*/

class Core {
public:

    Core(std::string defaultLib);
    ~Core();
    void mainLoop();


private:
    std::shared_ptr<Arcade::IDisplay> _display; ///< The display object.
    std::shared_ptr<Arcade::IGame> _game; ///< The game object.
    std::string _currentLib; ///< The current graphic library.
    std::string _currentGame; ///< The current game.
    std::vector<std::string> _libs; ///< The available graphic libraries.
    std::vector<std::string> _games; ///< The available games.
    bool _isRunning = false; ///< A boolean to know if the core is running.
    void manageEvent(Arcade::Event event);
    void refreshLibs();
    void loadAllLibs();

    public:
        /**
         * @brief An exception class for the Core class.
         */
        class InvalidStartLibException : public std::exception {
        public:
            InvalidStartLibException(std::string const &message) throw() : _message(message) {}
            const char *what() const throw() { return _message.c_str(); }
            ~InvalidStartLibException() throw() {}
        private:
            std::string _message;
        };
};
