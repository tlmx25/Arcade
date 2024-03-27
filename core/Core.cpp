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
    _display = std::unique_ptr<Arcade::IDisplay>(lib.getElement<Arcade::IDisplay *>("entryPointDisplay"));
    if (_display == nullptr)
        throw InvalidStartLibException("Impossible to load the library");
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
    Arcade::Event Lastevent;
    int nbTurn = 0;

    _isRunning = true;
    while (_isRunning) {
        event = _display->getInput();
        if (event != Arcade::Event::NONE)
            Lastevent = event;
        manageEvent(event);
        nbTurn = _display->playTurn();
        if (!nbTurn)
            continue;
        _display->clearWindow();
        if (_isInMenu)
            objects = menu();
        else {
            for (int i = 0; i < nbTurn; i++)
                objects = _game->Turn(Lastevent);
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
    if ((event >= Arcade::IN_A && event <= Arcade::IN_Z) || event == Arcade::Event::BACKSPACE)
        manageUsername(event);
    if (event == Arcade::Event::MENU)
        _isInMenu = true;
    if (event == Arcade::Event::NEXT_GAME)
        setGame(1);
    if (event == Arcade::Event::PREV_GAME)
        setGame(-1);
    if (event == Arcade::Event::NEXT_LIB)
        setDisplay(1);
    if (event == Arcade::Event::PREV_LIB)
        setDisplay(-1);
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
            std::cerr << e.what() << std::endl;
            continue;
        }
        std::cout << "lib: " << entry.path().string() << " is game: " << lib.isGameLib() << "is lib : "<< lib.isDisplayLib()<<  std::endl;
        if (lib.isGameLib())
            _gamesList.push_back(entry.path().string());
        else if (lib.isDisplayLib())
            _libsList.push_back(entry.path().string());
    }
}

/**
 * @brief Refresh the libraries list.
 *
 */

void Core::refreshLibs()
{
    _libsList.clear();
    _gamesList.clear();
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
    for (auto &game : _gamesList) {
        objects.push_back(std::make_shared<Arcade::Object>(x,60, Arcade::Type::Text, Arcade::Color::WHITE, getLibName(game)));
        x += 150;
    }
    objects.push_back(std::make_shared<Arcade::Object>(30,90, Arcade::Type::Text, Arcade::Color::WHITE, "Graphics:"));
    x = 180;
    for (auto &lib : _libsList) {
        objects.push_back(std::make_shared<Arcade::Object>(x,90, Arcade::Type::Text, Arcade::Color::WHITE, getLibName(lib)));
        x += 150;
    }
    objects.push_back(std::make_shared<Arcade::Object>(1500,120, Arcade::Type::Text, Arcade::Color::WHITE, "Username: " + _username));
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

/**
 * @brief Get the next library
 *
 * @param currentLib The current library.
 * @param libs The list of libraries.
 * @return std::string The next library.
 */
std::string Core::getNextLib(std::string const &currentLib, std::vector<std::string> const &libs)
{
    bool is_find = false;
    if (currentLib.empty() && !libs.empty())
        return libs.front();
    for (auto &lib : libs) {
        if (is_find)
            return lib;
        if (lib == currentLib)
            is_find = true;
    }
    if (is_find && !libs.empty())
        return libs.front();
    return "";
}

/**
 * @brief Get the previous library
 *
 * @param currentLib The current library.
 * @param libs The list of libraries.
 * @return std::string The previous library.
 */
std::string Core::getPreviousLib(std::string const &currentLib, std::vector<std::string> const &libs)
{
    bool is_find = false;
    std::string prev;

    if (currentLib.empty() && !libs.empty())
        return libs.back();
    for (auto &lib : libs) {
        if (lib == currentLib) {
            if (is_find)
                return prev;
            is_find = true;
        }
        prev = lib;
    }
    if (is_find && !libs.empty())
        return libs.back();
    return "";
}

/**
 * @brief Set the game
 *
 * @param PreviousOrNext The previous or next game, -1 for Previous, 1 for Next.
 */
void Core::setGame(int PreviousOrNext)
{
    std::string newGame;
    Arcade::IGame *game = nullptr;

    if (PreviousOrNext != 1 && PreviousOrNext != -1)
        return;
    if (PreviousOrNext == -1)
        newGame = getPreviousLib(_currentGame, _gamesList);
    else
        newGame = getNextLib(_currentGame, _gamesList);
    if (newGame.empty())
        return;
    try {
        CLibEncapsulation lib(newGame);
        game = lib.getElement<Arcade::IGame *>("entryPointGame");
        if (game == nullptr)
            throw InvalidStartLibException("Impossible to load the library");
    } catch (const CLibEncapsulation::LibException &e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    _game = std::unique_ptr<Arcade::IGame>(game);
    _currentGame = newGame;
    _isInMenu = false;
}

/**
 * @brief Set the display
 *
 * @param PreviousOrNext The previous or next display, -1 for Previous, 1 for Next.
 */
void Core::setDisplay(int PreviousOrNext)
{
    std::string newLib;
    Arcade::IDisplay *display;

    if (PreviousOrNext != 1 && PreviousOrNext != -1)
        return;
    if (PreviousOrNext == -1)
        newLib = getPreviousLib(_currentLib, _libsList);
    else
        newLib = getNextLib(_currentLib, _libsList);
    if (newLib.empty() || newLib == _currentLib)
        return;
    try {
        CLibEncapsulation lib(newLib);
        display = lib.getElement<Arcade::IDisplay *>("entryPointDisplay");
        if (display == nullptr)
            throw InvalidStartLibException("Impossible to load the library");
    } catch (const CLibEncapsulation::LibException &e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    _display = std::unique_ptr<Arcade::IDisplay>(display);
    _currentLib = newLib;
}

static const std::vector<std::pair<Arcade::Event, std::string >> keyEvents = {
    {Arcade::Event::IN_0, "0"},
    {Arcade::Event::IN_1, "1"},
    {Arcade::Event::IN_2, "2"},
    {Arcade::Event::IN_3, "3"},
    {Arcade::Event::IN_4, "4"},
    {Arcade::Event::IN_5, "5"},
    {Arcade::Event::IN_6, "6"},
    {Arcade::Event::IN_7, "7"},
    {Arcade::Event::IN_8, "8"},
    {Arcade::Event::IN_9, "9"},
    {Arcade::Event::IN_A, "a"},
    {Arcade::Event::IN_B, "b"},
    {Arcade::Event::IN_C, "c"},
    {Arcade::Event::IN_D, "d"},
    {Arcade::Event::IN_E, "e"},
    {Arcade::Event::IN_F, "f"},
    {Arcade::Event::IN_G, "g"},
    {Arcade::Event::IN_H, "h"},
    {Arcade::Event::IN_I, "i"},
    {Arcade::Event::IN_J, "j"},
    {Arcade::Event::IN_K, "k"},
    {Arcade::Event::IN_L, "l"},
    {Arcade::Event::IN_M, "m"},
    {Arcade::Event::IN_N, "n"},
    {Arcade::Event::IN_O, "o"},
    {Arcade::Event::IN_P, "p"},
    {Arcade::Event::IN_Q, "q"},
    {Arcade::Event::IN_R, "r"},
    {Arcade::Event::IN_S, "s"},
    {Arcade::Event::IN_T, "t"},
    {Arcade::Event::IN_U, "u"},
    {Arcade::Event::IN_V, "v"},
    {Arcade::Event::IN_W, "w"},
    {Arcade::Event::IN_X, "x"},
    {Arcade::Event::IN_Y, "y"},
    {Arcade::Event::IN_Z, "z"},
};

/**
 * @brief Manage the username
 *
 * @param event The event corresping to the letter.
 */

void Core::manageUsername(Arcade::Event event)
{
    if (event == Arcade::Event::BACKSPACE && !_username.empty()) {
        _username.pop_back();
        return;
    }
    for (auto &key : keyEvents) {
        if (key.first == event) {
            _username += key.second;
            return;
        }
    }
}
