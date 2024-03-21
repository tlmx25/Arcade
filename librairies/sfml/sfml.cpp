/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml
*/

#include "sfml.hpp"

/**
 * @brief Construct a new sfml::sfml object
*/
Arcade::sfml::sfml() : _window(sf::VideoMode(1920, 1080), "Arcade")
{
}

/**
 * @brief Destroy the sfml::sfml object
*/
Arcade::sfml::~sfml()
{
    _window.close();
}

/**
 * @brief Clear the window
*/
void Arcade::sfml::clearWindow()
{
    _window.clear(sf::Color::Black);
}

/**
 * @brief Update the window
*/
void Arcade::sfml::updateWindow()
{
    _window.display();
}

/**
 * @brief Draw an object
 *
 * @param object
*/
void Arcade::sfml::draw(std::shared_ptr<Arcade::Object> object)
{
    if (object->getType() == Arcade::Type::Circle)
        _drawCircle(object);
    else if (object->getType() == Arcade::Type::Rectangle)
        _drawRectangle(object);
    else if (object->getType() == Arcade::Type::Text)
        _drawText(object);
}

/**
 * @brief Get the input
 *
 * @return Arcade::Event
*/
Arcade::Event Arcade::sfml::getInput()
{
    sf::Event event = {};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return Arcade::Event::ESCAPE;
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
                return Arcade::Event::ESCAPE;
            if (event.key.code == sf::Keyboard::Up)
                return Arcade::Event::GAME_UP;
            if (event.key.code == sf::Keyboard::Down)
                return Arcade::Event::GAME_DOWN;
            if (event.key.code == sf::Keyboard::Left)
                return Arcade::Event::GAME_LEFT;
            if (event.key.code == sf::Keyboard::Right)
                return Arcade::Event::GAME_RIGHT;
            if (event.key.code == sf::Keyboard::Space)
                return Arcade::Event::GAME_SHOOT;
            if (event.key.code == sf::Keyboard::F1)
                return Arcade::Event::PREV_GAME;
            if (event.key.code == sf::Keyboard::F2)
                return Arcade::Event::NEXT_GAME;
            if (event.key.code == sf::Keyboard::F3)
                return Arcade::Event::PREV_LIB;
            if (event.key.code == sf::Keyboard::F4)
                return Arcade::Event::NEXT_LIB;
            if (event.key.code == sf::Keyboard::F5)
                return Arcade::Event::GAME_RESTART;
            if (event.key.code == sf::Keyboard::F8)
                return Arcade::Event::MENU;
            if (event.key.code == sf::Keyboard::F10)
                return Arcade::Event::REFRESH;
            if (event.key.code == sf::Keyboard::Enter)
                return Arcade::Event::ENTER;
            if (event.key.code == sf::Keyboard::BackSpace)
                return Arcade::Event::BACKSPACE;
        }
    }
    return Arcade::Event::NONE;
}

/**
 * @brief Play the next turn of the game
 *
 * @return int
*/
int Arcade::sfml::playTurn()
{
    // TODO: Implement this function
    return 0;
}

/**
 * @brief Get the color
 * 
 * @param color
 * @return sf::Color
*/
sf::Color Arcade::sfml::_getColor(Arcade::Color color)
{
    if (color == Arcade::Color::RED)
        return sf::Color::Red;
    if (color == Arcade::Color::GREEN)
        return sf::Color::Green;
    if (color == Arcade::Color::BLUE)
        return sf::Color::Blue;
    if (color == Arcade::Color::YELLOW)
        return sf::Color::Yellow;
    if (color == Arcade::Color::WHITE)
        return sf::Color::White;
    if (color == Arcade::Color::BLACK)
        return sf::Color::Black;
    if (color == Arcade::Color::GREY)
        return sf::Color(128, 128, 128);
    if (color == Arcade::Color::PURPLE)
        return sf::Color::Magenta;
    // TODO
    // if (color == Arcade::Color::UNKNOWN)
    //     return sf::Color::Black;
    return sf::Color::Black;
}

/**
 * @brief Draw a circle
 *
 * @param object
*/
void Arcade::sfml::_drawCircle(std::shared_ptr<Arcade::Object> object)
{
    sf::CircleShape circle(OBJECT_SIZE / 2);

    circle.setFillColor(_getColor(object->getColor()));
    circle.setPosition(object->getPosition().getX(), object->getPosition().getY());
    _window.draw(circle);
}

/**
 * @brief Draw a rectangle
 *
 * @param object
*/
void Arcade::sfml::_drawRectangle(std::shared_ptr<Arcade::Object> object)
{
    sf::RectangleShape rectangle(sf::Vector2f(OBJECT_SIZE, OBJECT_SIZE));

    rectangle.setFillColor(_getColor(object->getColor()));
    rectangle.setPosition(object->getPosition().getX(), object->getPosition().getY());
    _window.draw(rectangle);
}

/**
 * @brief Draw a text
 *
 * @param object
*/
void Arcade::sfml::_drawText(std::shared_ptr<Arcade::Object> object)
{
    sf::Text text;
    sf::Font font;

    if (!font.loadFromFile("../assets/arial.ttf"))
        return;
    text.setFont(font);
    text.setString(object->getAsset());
    // TODO
    // text.setCharacterSize(OBJECT_SIZE);
    text.setFillColor(_getColor(object->getColor()));
    text.setPosition(object->getPosition().getX(), object->getPosition().getY());
    _window.draw(text);
}