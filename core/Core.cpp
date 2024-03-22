/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <filesystem>
#include "Core.hpp"

/**
 * @brief Construct a new Core object
 *
 * @param defaultLib The default graphic library to use.
 *
 */
Core::Core(std::string defaultLib)
{
    _currentLib = defaultLib;
    CLibEncapsulation lib(defaultLib);
    if (!lib.isDisplayLib())
        throw InvalidStartLibException("Invalid library type");
    _display = std::shared_ptr<Arcade::IDisplay>(lib.getElement<Arcade::IDisplay *>("entryPointDisplay"));

    _currentGame = "";
    _game = nullptr;
}

/**
 * @brief Destroy the Core object
 *
 */
Core::~Core() = default;

/**
 * @brief Run the core
 *
 */
void Core::mainLoop()
{
    std::vector<std::shared_ptr<Arcade::Object>> objects;
    Arcade::Event event;
    int nbTurn = 0;
    _game->init();

    _isRunning = true;
    while (_isRunning) {
        nbTurn = _display->playTurn();
        if (!nbTurn)
            continue;
        _display->clearWindow();
        event = _display->getInput();
        for (int i = 0; i < nbTurn; i++)
            objects = _game->Turn(event);
        for (auto &object : objects) {
            _display->draw(object);
        }
        _display->updateWindow();
    }
}

/**
 * @brief Manage the event
 *
 * @param event The event to manage.
 */
void Core::manageEvent(Arcade::Event event)
{
    if (event == Arcade::Event::ESCAPE)
        _isRunning = false;
    if (event == Arcade::Event::REFRESH)
        refreshLibs();
}

/**
 * @brief Load all the libraries for next or previous games or graphic libraries.
 *
 */
void Core::loadAllLibs()
{
    CLibEncapsulation lib;

    for (const auto &entry : std::filesystem::directory_iterator("lib")) {
        if (entry.path().extension() != ".so" || entry.path().filename().string().find("menu") != 0)
            continue;
        try {
            lib.openLib(entry.path().string());
        } catch (const CLibEncapsulation::LibException &e) {
            continue;
        }
        if (lib.isGameLib())
            _games.push_back(entry.path().string());
        else if (lib.isDisplayLib())
            _libs.push_back(entry.path().string());
    }
}

/**
 * @brief Refresh the libraries list.
 *
 */

void Core::refreshLibs()
{
    _libs.clear();
    _games.clear();
    loadAllLibs();
}

/**
 * @brief logic for menu
 *
 * @return std::vector<std::shared_ptr<Arcade::Object>> The menu element.
 */
std::vector<std::shared_ptr<Arcade::Object>> Core::menu()
{
    std::vector<std::shared_ptr<Arcade::Object>> objects;
    Arcade::Event event;

    while (_isInMenu) {
        _display->updateWindow();
        event = _display->getInput();
        manageEvent(event);
    }
    return objects;
}
