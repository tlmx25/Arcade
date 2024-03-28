/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#include "snake.hpp"

snake::Player::Player()
{
    _snake.push_back(std::make_shared<Arcade::Object>(22 * SIZE, 12 * SIZE, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_left.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(23 * SIZE, 12 * SIZE, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(24 * SIZE, 12 * SIZE, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(25 * SIZE, 12 * SIZE, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/head_right.png"));

    _directions.push_back(Arcade::GAME_RIGHT);
    _directions.push_back(Arcade::GAME_RIGHT);
    _directions.push_back(Arcade::GAME_RIGHT);
    _directions.push_back(Arcade::GAME_RIGHT);
}

void snake::Player::set_direction(Arcade::Event direction)
{
    _direction = direction;
}

Arcade::Event snake::Player::get_direction()
{
    return _direction;
}

Arcade::Event snake::Player::get_last_direction()
{
    return _last_direction;
}

void snake::Player::set_last_direction(Arcade::Event direction)
{
    _last_direction = direction;
}

void snake::Player::moove_player()
{
    int x = 0;
    int y = 0;
    std::shared_ptr<Arcade::Object> tmp;
    std::vector<Arcade::Event> _tmp_directions;

    if (get_direction() == Arcade::NONE) {
        for (auto &obj : _snake) {
            obj->setPosition(obj->getPosition().getX() + SIZE, obj->getPosition().getY());
        }
    }
    if (get_direction() == Arcade::GAME_LEFT) {
        for (size_t i = _snake.size(); i != 0 ; i--) {
            if (i == _snake.size()) {
                x = _snake[i]->getPosition().getX();
                y = _snake[i]->getPosition().getY();
                if (get_last_direction() == Arcade::GAME_UP) {
                    _directions[i] = Arcade::GAME_LEFT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_left.png");
                    _snake[i]->setPosition(x - SIZE, y);
                } else if (get_last_direction() == Arcade::GAME_DOWN) {
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_right.png");
                    _snake[i]->setPosition(x + SIZE, y);
                } else if (get_last_direction() == Arcade::GAME_LEFT) {
                    _directions[i] = Arcade::GAME_DOWN;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_down.png");
                    _snake[i]->setPosition(x, y + SIZE);
                } else {
                    _directions[i] = Arcade::GAME_UP;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_up.png");
                    _snake[i]->setPosition(x - SIZE, y - SIZE);
                }
            } else {
                _snake[i]->setPosition(x, y);
            }
        }
    }

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
    for (int i = 2 ; i < 23 ; i++) {
        std::vector<std::shared_ptr<Arcade::Object>> line;
        for (int j = 9 ; j < 40 ; j++) {
            if (j % 2 == color) {
                line.push_back(std::make_shared<Arcade::Object>(j * SIZE, i * SIZE, Arcade::Type::Rectangle, Arcade::Color::GREEN,
                                                                "librairies/assets/snake/grass.png"));
            } else {
                line.push_back(std::make_shared<Arcade::Object>(j * SIZE, i * SIZE, Arcade::Type::Rectangle, Arcade::Color::BLUE,
                                                                "librairies/assets/snake/grass2.png"));
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

std::vector<std::shared_ptr<Arcade::Object>> snake::Turn(Arcade::Event event)
{
    this->_objects.clear();
    this->_snake_player.set_direction(event);
    this->_snake_player.moove_player();
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