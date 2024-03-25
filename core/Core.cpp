/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include <filesystem>
#include "Core.hpp"

#include "../librairies/sfml/sfml.hpp"
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
    std::cout << "Library loaded" << std::endl;
//    _display = std::shared_ptr<Arcade::IDisplay>(new Arcade::sfml());
    _display = std::shared_ptr<Arcade::IDisplay>(lib.getElement<Arcade::IDisplay *>("entryPointDisplay"));
    if (_display == nullptr)
        throw InvalidStartLibException("Impossible to load the library");
    std::cout << "Display loaded" << std::endl;
    loadAllLibs();
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

    _isRunning = true;
    while (_isRunning) {
        event = _display->getInput();
        manageEvent(event);
        nbTurn = _display->playTurn();
        if (!nbTurn)
            continue;
        _display->clearWindow();
        if (_isInMenu)
            objects = menu();
        else {
            for (int i = 0; i < nbTurn; i++)
                objects = _game->Turn(event);
        }
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
        std::cout << entry.path() << std::endl;
        if (entry.path().extension() != ".so") {
            continue;
        }
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

    objects.push_back(std::make_shared<Arcade::Object>(30,30, Arcade::Type::Text, Arcade::Color::WHITE, "Arcade"));
    objects.push_back(std::make_shared<Arcade::Object>(30,60, Arcade::Type::Text, Arcade::Color::WHITE, "Games:"));
    int x = 180;
    for (auto &game : _games) {
        objects.push_back(std::make_shared<Arcade::Object>(x,60, Arcade::Type::Text, Arcade::Color::WHITE, getLibName(game)));
        x += 150;
    }
    objects.push_back(std::make_shared<Arcade::Object>(30,90, Arcade::Type::Text, Arcade::Color::WHITE, "Graphics:"));
    x = 180;
    for (auto &lib : _libs) {
        objects.push_back(std::make_shared<Arcade::Object>(x,90, Arcade::Type::Text, Arcade::Color::WHITE, getLibName(lib)));
        x += 150;
    }
    return objects;
}

/**
 * @brief Get the name of the library
 *
 * @param path The path of the library.
 * @return std::string The name of the library.
 */
std::string Core::getLibName(std::string const &path)
{
    std::string name = path.substr(path.find_last_of('/') + 1);
    return name.substr(0, name.find_last_of('.'));
}
