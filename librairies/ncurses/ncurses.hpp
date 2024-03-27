/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ncurses
*/

#pragma once

#include <ncurses.h>
#include "IDisplay.hpp"
#include <ctime>
#include <cmath>
#include <vector>
#define OBJECT_SIZE 40

/**
 * @file ncurses.hpp
 * @brief ncurses class for the Arcade project
 **/

namespace Arcade {
/**
 * @class ncurses
 * @brief A class to represent the ncurses library in the Arcade project.
 *
 * This class contains methods to initialize the window, destroy the window, display the window, clear the window, draw an object, and get the input.
 */
    class ncurses : public IDisplay {

    public:
        ncurses();
        ~ncurses();
        void clearWindow() override;
        void updateWindow() override;
        void draw(std::shared_ptr<Arcade::Object> object) override;
        Arcade::Event getInput() override;
        int playTurn() override;

    private:
        clock_t _clock;
        void define_pair_colors();
        int _getColor(Arcade::Color color);
        void drawCircle(const std::shared_ptr<Arcade::Object> object) override;
        void drawRectangle(const std::shared_ptr<Arcade::Object> object) override;
        void drawText(const std::shared_ptr<Arcade::Object> object) override;
    };
}

extern "C" Arcade::ncurses * entryPointDisplay();
