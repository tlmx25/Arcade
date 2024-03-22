/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml _lib
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "IDisplay.hpp"
#define OBJECT_SIZE 40

/**
 * @file sfml.hpp
 * @brief sfml class for the Arcade project
 **/

namespace Arcade {
/**
 * @class sfml
 * @brief A class to represent the sfml library in the Arcade project.
 *
 * This class contains methods to initialize the window, destroy the window, display the window, clear the window, draw an object, and get the input.
 */
    class sfml : public IDisplay {

    public:
        sfml();
        ~sfml();
        void clearWindow() override;
        void updateWindow() override;
        void draw(std::shared_ptr<Arcade::Object> object) override;
        Arcade::Event getInput() override;
        int playTurn() override;

    private:
        sf::RenderWindow _window;
        sf::Clock _clock;
        sf::Color _getColor(Arcade::Color color);
        void drawCircle(const std::shared_ptr<Arcade::Object> object) override;
        void drawRectangle(const std::shared_ptr<Arcade::Object> object) override;
        void drawText(const std::shared_ptr<Arcade::Object> object) override;
    };
}
