/*
** EPITECH PROJECT, 2024
** arcare
** File description:
** sdl2
*/

#pragma once

#include "IDisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <vector>

/**
 * @file sdl2.hpp
 * @brief sdl2 class for the Arcade project
 **/

namespace Arcade {
/**
 * @class sdl2
 * @brief A class to represent the sdl2 library in the Arcade project.
 *
 * This class contains methods to initialize the window, destroy the window, display the window, clear the window, draw an object, and get the input.
 */
    class sdl2 : public IDisplay {

    public:
        sdl2();
        ~sdl2();
        void clearWindow() override;
        void updateWindow() override;
        void draw(std::shared_ptr<Arcade::Object> object) override;
        Arcade::Event getInput() override;
        int playTurn() override;

    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Surface *_surface;
        std::vector<std::pair<std::string, SDL_Texture *>> _textures;
        clock_t _clock;
        bool _loadTexture(const std::string &path);
        void drawCircle(const std::shared_ptr<Arcade::Object> object) override;
        void drawRectangle(const std::shared_ptr<Arcade::Object> object) override;
        void drawText(const std::shared_ptr<Arcade::Object> object) override;
    };
}

extern "C" Arcade::sdl2 * entryPointDisplay();
