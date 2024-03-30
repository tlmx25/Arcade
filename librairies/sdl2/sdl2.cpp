/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sdl2
*/

#include "sdl2.hpp"

const std::vector<std::pair<int, Arcade::Event>> keyEvents = {
    {SDLK_ESCAPE, Arcade::Event::ESCAPE},
    {SDLK_UP, Arcade::Event::GAME_UP},
    {SDLK_DOWN, Arcade::Event::GAME_DOWN},
    {SDLK_LEFT, Arcade::Event::GAME_LEFT},
    {SDLK_RIGHT, Arcade::Event::GAME_RIGHT},
    {SDLK_SPACE, Arcade::Event::GAME_SHOOT},
    {SDLK_F1, Arcade::Event::PREV_GAME},
    {SDLK_F2, Arcade::Event::NEXT_GAME},
    {SDLK_F3, Arcade::Event::PREV_LIB},
    {SDLK_F4, Arcade::Event::NEXT_LIB},
    {SDLK_F5, Arcade::Event::GAME_RESTART},
    {SDLK_F8, Arcade::Event::MENU},
    {SDLK_F10, Arcade::Event::REFRESH},
    {SDLK_RETURN, Arcade::Event::ENTER},
    {SDLK_BACKSPACE, Arcade::Event::BACKSPACE},
    {'1', Arcade::Event::IN_1},
    {'2', Arcade::Event::IN_2},
    {'3', Arcade::Event::IN_3},
    {'4', Arcade::Event::IN_4},
    {'5', Arcade::Event::IN_5},
    {'6', Arcade::Event::IN_6},
    {'7', Arcade::Event::IN_7},
    {'8', Arcade::Event::IN_8},
    {'9', Arcade::Event::IN_9},
    {'0', Arcade::Event::IN_0},
    {'a', Arcade::Event::IN_A},
    {'b', Arcade::Event::IN_B},
    {'c', Arcade::Event::IN_C},
    {'d', Arcade::Event::IN_D},
    {'e', Arcade::Event::IN_E},
    {'f', Arcade::Event::IN_F},
    {'g', Arcade::Event::IN_G},
    {'h', Arcade::Event::IN_H},
    {'i', Arcade::Event::IN_I},
    {'j', Arcade::Event::IN_J},
    {'k', Arcade::Event::IN_K},
    {'l', Arcade::Event::IN_L},
    {'m', Arcade::Event::IN_M},
    {'n', Arcade::Event::IN_N},
    {'o', Arcade::Event::IN_O},
    {'p', Arcade::Event::IN_P},
    {'q', Arcade::Event::IN_Q},
    {'r', Arcade::Event::IN_R},
    {'s', Arcade::Event::IN_S},
    {'t', Arcade::Event::IN_T},
    {'u', Arcade::Event::IN_U},
    {'v', Arcade::Event::IN_V},
    {'w', Arcade::Event::IN_W},
    {'x', Arcade::Event::IN_X},
    {'y', Arcade::Event::IN_Y},
    {'z', Arcade::Event::IN_Z},
};

/**
 * @brief Construct a new sdl2 object
 *
 */
Arcade::sdl2::sdl2()
{
    //TODO : Throw errors instead of exit
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    _surface = SDL_GetWindowSurface(_window);
    if (_surface == nullptr) {
        std::cerr << "SDL_GetWindowSurface Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(84);
    }
    _clock = clock();
}

/**
 * @brief Destroy the sdl2 object
 *
 */
Arcade::sdl2::~sdl2()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    _textures.clear();
}

/**
 * @brief Clear the window
 *
 */
void Arcade::sdl2::clearWindow()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
}

/**
 * @brief Update the window
 *
 */
void Arcade::sdl2::updateWindow()
{
    SDL_RenderPresent(_renderer);
}

/**
 * @brief Draw an object
 *
 * @param object
 */
void Arcade::sdl2::draw(std::shared_ptr<Arcade::Object> object)
{
    if (object->getType() == Arcade::Type::Circle)
        drawCircle(object);
    else if (object->getType() == Arcade::Type::Rectangle)
        drawRectangle(object);
    else if (object->getType() == Arcade::Type::Text)
        drawText(object);
}

/**
 * @brief Get the input
 *
 * @return Arcade::Event
 */
Arcade::Event Arcade::sdl2::getInput()
{
    SDL_Event _event = {};

    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT)
            return Arcade::Event::ESCAPE;
        for (auto &key : keyEvents) {
            if (_event.key.keysym.sym == key.first)
                return key.second;
        }
    }
    return Arcade::Event::NONE;
}

/**
 * @brief Play a turn
 *
 * @return int
 */
int Arcade::sdl2::playTurn()
{
    clock_t new_clock = clock();
    int time = (new_clock - _clock) / CLOCKS_PER_SEC;

    if (time >= 1) {
        _clock = new_clock;
        return time;
    }
    return 0;
}

/**
 * @brief Load a texture
 * 
 * @param path
 * 
 * @return Bool: true if the texture is loaded, false otherwise
*/
bool Arcade::sdl2::_loadTexture(const std::string &path)
{
    if (_textures.size() > 0) {
        for (auto &texture : _textures) {
            if (texture.first == path)
                return true;
        }
    }
    SDL_Texture *texture = IMG_LoadTexture(_renderer, path.c_str());
    if (texture == nullptr) {
        return false;
    }
    _textures.push_back(std::make_pair(path, texture));
    return true;
}