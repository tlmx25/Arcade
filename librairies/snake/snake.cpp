/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#include "snake.hpp"

snake::Player::Player()
{
    _snake.push_back(std::make_shared<Arcade::Object>(10, 10, Arcade::Type::Rectangle, Arcade::Color::GREEN, ASSET_PATH"snake/tail_left.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(10, 11, Arcade::Type::Rectangle, Arcade::Color::GREEN, ASSET_PATH"snake/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(10, 12, Arcade::Type::Rectangle, Arcade::Color::GREEN, ASSET_PATH"snake/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(10, 13, Arcade::Type::Rectangle, Arcade::Color::GREEN, ASSET_PATH"snake/head_right.png"));
}

std::vector<std::shared_ptr<Arcade::Object>> snake::Player::get_snake() {
    return _snake;
}

snake::snake()
{
    this->_initMap();
    _apple = std::make_shared<Arcade::Object>(10, 10, Arcade::Type::Rectangle, Arcade::Color::RED, ASSET_PATH"apple.png");
    _snake_player = Player();
}

snake::~snake()
{
}

void snake::_initMap()
{
    int color = 0;
    for (int i = 0 ; i < 20 ; i++) {
        std::vector<std::shared_ptr<Arcade::Object>> line;
        for (int j = 0 ; j < 20 ; j++) {
            if (j % 2 == color) {
                line.push_back(std::make_shared<Arcade::Object>(i, j, Arcade::Type::Rectangle, Arcade::Color::GREEN,
                                                                ASSET_PATH"grass.png"));
                printf("green ");
            } else {
                line.push_back(std::make_shared<Arcade::Object>(i, j, Arcade::Type::Rectangle, Arcade::Color::GREEN,
                                                                ASSET_PATH"grass2.png"));
                printf("green2 ");
            }
        }
        printf("\n");
        color = !color;
        this->_map.push_back(line);
    }
}

void snake::createObects()
{
    for (auto &line : this->_map) {
        for (auto &obj : line) {
            this->_objects.push_back(obj);
        }
    }
    for (auto &obj : this->_snake_player.get_snake()) {
        this->_objects.push_back(obj);
    }
}

std::vector<std::shared_ptr<Arcade::Object>> snake::Turn(Arcade::Event event) {
    this->_objects.clear();
    createObects();
    return this->_objects;
}

int snake::getScore()
{
    return 0;
}

extern "C" Arcade::IGame *entryPointGame()
{
    return (new snake());
}