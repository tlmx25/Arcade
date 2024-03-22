/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** sfml
*/

#include "sfml.hpp"

const std::vector<std::pair<sf::Keyboard::Key, Arcade::Event>> keyEvents = {
    {sf::Keyboard::Escape, Arcade::Event::ESCAPE},
    {sf::Keyboard::Up, Arcade::Event::GAME_UP},
    {sf::Keyboard::Down, Arcade::Event::GAME_DOWN},
    {sf::Keyboard::Left, Arcade::Event::GAME_LEFT},
    {sf::Keyboard::Right, Arcade::Event::GAME_RIGHT},
    {sf::Keyboard::Space, Arcade::Event::GAME_SHOOT},
    {sf::Keyboard::F1, Arcade::Event::PREV_GAME},
    {sf::Keyboard::F2, Arcade::Event::NEXT_GAME},
    {sf::Keyboard::F3, Arcade::Event::PREV_LIB},
    {sf::Keyboard::F4, Arcade::Event::NEXT_LIB},
    {sf::Keyboard::F5, Arcade::Event::GAME_RESTART},
    {sf::Keyboard::F8, Arcade::Event::MENU},
    {sf::Keyboard::F10, Arcade::Event::REFRESH},
    {sf::Keyboard::Enter, Arcade::Event::ENTER},
    {sf::Keyboard::BackSpace, Arcade::Event::BACKSPACE},
    {sf::Keyboard::Num1, Arcade::Event::IN_1},
    {sf::Keyboard::Num2, Arcade::Event::IN_2},
    {sf::Keyboard::Num3, Arcade::Event::IN_3},
    {sf::Keyboard::Num4, Arcade::Event::IN_4},
    {sf::Keyboard::Num5, Arcade::Event::IN_5},
    {sf::Keyboard::Num6, Arcade::Event::IN_6},
    {sf::Keyboard::Num7, Arcade::Event::IN_7},
    {sf::Keyboard::Num8, Arcade::Event::IN_8},
    {sf::Keyboard::Num9, Arcade::Event::IN_9},
    {sf::Keyboard::Num0, Arcade::Event::IN_0},
    {sf::Keyboard::A, Arcade::Event::IN_A},
    {sf::Keyboard::B, Arcade::Event::IN_B},
    {sf::Keyboard::C, Arcade::Event::IN_C},
    {sf::Keyboard::D, Arcade::Event::IN_D},
    {sf::Keyboard::E, Arcade::Event::IN_E},
    {sf::Keyboard::F, Arcade::Event::IN_F},
    {sf::Keyboard::G, Arcade::Event::IN_G},
    {sf::Keyboard::H, Arcade::Event::IN_H},
    {sf::Keyboard::I, Arcade::Event::IN_I},
    {sf::Keyboard::J, Arcade::Event::IN_J},
    {sf::Keyboard::K, Arcade::Event::IN_K},
    {sf::Keyboard::L, Arcade::Event::IN_L},
    {sf::Keyboard::M, Arcade::Event::IN_M},
    {sf::Keyboard::N, Arcade::Event::IN_N},
    {sf::Keyboard::O, Arcade::Event::IN_O},
    {sf::Keyboard::P, Arcade::Event::IN_P},
    {sf::Keyboard::Q, Arcade::Event::IN_Q},
    {sf::Keyboard::R, Arcade::Event::IN_R},
    {sf::Keyboard::S, Arcade::Event::IN_S},
    {sf::Keyboard::T, Arcade::Event::IN_T},
    {sf::Keyboard::U, Arcade::Event::IN_U},
    {sf::Keyboard::V, Arcade::Event::IN_V},
    {sf::Keyboard::W, Arcade::Event::IN_W},
    {sf::Keyboard::X, Arcade::Event::IN_X},
    {sf::Keyboard::Y, Arcade::Event::IN_Y},
    {sf::Keyboard::Z, Arcade::Event::IN_Z}
};


/**
 * @brief Construct a new sfml::sfml object
*/
Arcade::sfml::sfml() : _window(sf::VideoMode(1920, 1080), "Arcade")
{
    _clock = sf::Clock();
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
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return Arcade::Event::ESCAPE;
        for (auto key : keyEvents) {
            if (sf::Keyboard::isKeyPressed(key.first))
                return key.second;
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
    sf::Time time = _clock.getElapsedTime();
    float seconds = time.asSeconds();

    if (seconds >= 1.0f) {
        _clock.restart();
        return static_cast<int>(seconds);
    }
    _clock.restart();
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
    if (color == Arcade::Color::UNKNOWN)
        return sf::Color::Black;
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
    // TODO: tests ??
    // text.setCharacterSize(OBJECT_SIZE);
    text.setFillColor(_getColor(object->getColor()));
    text.setPosition(object->getPosition().getX(), object->getPosition().getY());
    _window.draw(text);
}