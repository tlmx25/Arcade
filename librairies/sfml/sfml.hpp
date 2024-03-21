/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml _lib
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "IDisplay.hpp"
#include "Object.hpp"

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
        /**
         * @brief Construct a new sfml object
         *
         */
        sfml();

        /**
         * @brief Destroy the sfml object
         *
         */
        ~sfml() override;

        /**
         * @brief Clear the window
         */
        void clearWindow() override;

        /**
         * @brief Draw the object
         *
         * @param object
         */
        void draw(std::shared_ptr<Arcade::Object> object) override;

        /**
         * @brief Get the input
         *
         * @return Event
         */
        Arcade::Event getInput() override;
    private:
        sf::RenderWindow _window;
        sf::Clock _clock;

        /**
         * @brief Get the color
         *
         * @param color
         * @return sf::Color
         */
        sf::Color _getColor(Arcade::Color color);

        /**
         * @brief Draw a circle
         * 
         * @param object
         */
        void _drawCircle(std::shared_ptr<Arcade::Object> object);

        /**
         * @brief Draw a rectangle
         * 
         * @param object
         */
        void _drawRectangle(std::shared_ptr<Arcade::Object> object);

        /**
         * @brief Draw a text
         * 
         * @param object
         */
        void _drawText(std::shared_ptr<Arcade::Object> object);
    };
}
