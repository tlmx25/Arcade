/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#include "snake.hpp"

snake::Player::Player()
{
    _snake.push_back(std::make_shared<Arcade::Object>(22 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_left.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(23 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(24 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(25 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/head_right.png"));

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

void snake::Player::eat() {
    if (_directions[0] == Arcade::Event::GAME_UP) {
        _snake[0]->setAsset("librairies/assets/snake/snake/body_vertical.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX(), _snake[0]->getPosition().getY() + 1, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_down.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_UP);
    }
    if (_directions[0] == Arcade::Event::GAME_DOWN) {
        _snake[0]->setAsset("librairies/assets/snake/snake/body_vertical.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX(), _snake[0]->getPosition().getY() - 1, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_up.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_DOWN);
    }
    if (_directions[0] == Arcade::Event::GAME_LEFT) {
        _snake[0]->setAsset("librairies/assets/snake/snake/body_horizontal.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX() + 1, _snake[0]->getPosition().getY(), Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_right.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_LEFT);
    }
    if (_directions[0] == Arcade::Event::GAME_RIGHT) {
        _snake[0]->setAsset("librairies/assets/snake/snake/body_horizontal.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX() - 1, _snake[0]->getPosition().getY(), Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_left.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_RIGHT);
    }
}

bool snake::Player::is_eating(std::shared_ptr<Arcade::Object> apple)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    if (_snake[_snake.size() - 1]->getPosition().getX() == apple->getPosition().getX() && _snake[_snake.size() - 1]->getPosition().getY() == apple->getPosition().getY()) {
        eat();
        std::vector<std::pair<int, int>> freePositions;
        for (int i = 9; i < 40; i++) {
            for (int j = 2; j < 23; j++) {
                freePositions.push_back({i, j});
            }
        }
        std::uniform_int_distribution<int> distribution(0, (int)freePositions.size() - 1);
        int randomIndex = distribution(gen);
        apple->setPosition(freePositions[randomIndex].first, freePositions[randomIndex].second);
        return true;
    }
    return false;
}

bool snake::Player::is_dead()
{
    size_t size = _snake.size() - 1;
    for (size_t i = 0; i < _snake.size() - 2; i++) {
        if (_snake[size]->getPosition().getX() == _snake[i]->getPosition().getX() && _snake[size]->getPosition().getY() == _snake[i]->getPosition().getY()) {
            return true;
        }
    }

    if (_snake[size]->getPosition().getX() < 8 || _snake[size]->getPosition().getX() > 40 || _snake[size]->getPosition().getY() < 1 || _snake[size]->getPosition().getY() > 23) {
        return true;
    }
    return false;
}

bool snake::Player::he_win()
{
    if (_snake.size() == 31 * 21)
        return true;
    return false;
}
int snake::Player::moove_player()
{
    int x, y, x_tmp, y_tmp = 0;
    bool check = false;
    std::shared_ptr<Arcade::Object> tmp;
    std::vector<Arcade::Event> _tmp_directions = _directions;

    if (get_direction() == Arcade::NONE) {
        for (size_t i = _snake.size() - 1; i != 0; i--) {
            if (i + 1 == _snake.size()) {
                x = _snake[i]->getPosition().getX();
                y = _snake[i]->getPosition().getY();
                if (_directions[i] == Arcade::GAME_UP) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_up.png");
                    _snake[i]->setPosition(x, y - 1);
                } else if (_directions[i] == Arcade::GAME_DOWN) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_down.png");
                    _snake[i]->setPosition(x, y + 1);
                } else if (_directions[i] == Arcade::GAME_LEFT) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_left.png");
                    _snake[i]->setPosition(x - 1, y);
                } else {
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_right.png");
                    _snake[i]->setPosition(x + 1, y);
                }
            } else {
                x_tmp = _snake[i]->getPosition().getX();
                y_tmp = _snake[i]->getPosition().getY();
                _snake[i]->setPosition(x, y);
                x = x_tmp;
                y = y_tmp;
            }
        }
        _snake[0]->setPosition(x, y);
        check = true;
    }
    if (get_direction() == Arcade::GAME_LEFT && !check) {
        for (size_t i = _snake.size() - 1; i != 0; i--) {
            if (i + 1 == _snake.size()) {
                x = _snake[i]->getPosition().getX();
                y = _snake[i]->getPosition().getY();
                if (_directions[i] == Arcade::GAME_UP) {
                    _directions[i] = Arcade::GAME_LEFT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_left.png");
                    _snake[i]->setPosition(x - 1, y);
                } else if (_directions[i] == Arcade::GAME_DOWN) {
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_right.png");
                    _snake[i]->setPosition(x + 1, y);
                } else if (_directions[i] == Arcade::GAME_LEFT) {
                    _directions[i] = Arcade::GAME_DOWN;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_down.png");
                    _snake[i]->setPosition(x, y + 1);
                } else {
                    _directions[i] = Arcade::GAME_UP;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_up.png");
                    _snake[i]->setPosition(x, y - 1);
                }
            } else {

                x_tmp = _snake[i]->getPosition().getX();
                y_tmp = _snake[i]->getPosition().getY();
                _snake[i]->setPosition(x, y);
                x = x_tmp;
                y = y_tmp;
            }
        }
        _snake[0]->setPosition(x, y);
        check = true;
    }
    if (get_direction() == Arcade::GAME_RIGHT && !check) {
        for (size_t i = _snake.size() - 1; i != 0; i--) {
            if (i + 1 == _snake.size()) {
                x = _snake[i]->getPosition().getX();
                y = _snake[i]->getPosition().getY();
                if (_directions[i] == Arcade::GAME_UP) {
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_right.png");
                    _snake[i]->setPosition(x + 1, y);
                } else if (_directions[i] == Arcade::GAME_DOWN) {
                    _directions[i] = Arcade::GAME_LEFT;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_left.png");
                    _snake[i]->setPosition(x - 1, y);
                } else if (_directions[i] == Arcade::GAME_LEFT) {
                    _directions[i] = Arcade::GAME_UP;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_up.png");
                    _snake[i]->setPosition(x, y - 1);
                } else {
                    _directions[i] = Arcade::GAME_DOWN;
                    _snake[i]->setAsset("librairies/assets/snake/snake/head_down.png");
                    _snake[i]->setPosition(x, y + 1);
                }
            } else {
                x_tmp = _snake[i]->getPosition().getX();
                y_tmp = _snake[i]->getPosition().getY();
                _snake[i]->setPosition(x, y);
                x = x_tmp;
                y = y_tmp;
            }
        }
        _snake[0]->setPosition(x, y);
        check = true;
    }

    if (check) {
        for (size_t i = _snake.size() - 2; i != 0; i--) {
            if (_directions[i + 1] == Arcade::GAME_UP) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 1)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_vertical.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_topright.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == -1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_topleft.png");
                }
                _tmp_directions[i] = Arcade::GAME_UP;
            }
            if (_directions[i + 1] == Arcade::GAME_DOWN) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == -1)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_vertical.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_bottomright.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == -1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_bottomleft.png");
                }
                _tmp_directions[i] = Arcade::GAME_DOWN;
            }
            if (_directions[i + 1] == Arcade::GAME_LEFT) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_horizontal.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 1)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_bottomleft.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == -1)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_topleft.png");
                }
                _tmp_directions[i] = Arcade::GAME_LEFT;
            }
            if (_directions[i + 1] == Arcade::GAME_RIGHT) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == -1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_horizontal.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 1)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_bottomright.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == -1)) {
                    _snake[i]->setAsset("librairies/assets/snake/snake/body_topright.png");
                }
                _tmp_directions[i] = Arcade::GAME_RIGHT;
            }
        }
        if (_directions[1] == Arcade::GAME_UP) {
            _snake[0]->setAsset("librairies/assets/snake/snake/tail_down.png");
            _tmp_directions[0] = Arcade::GAME_UP;
        }
        if (_directions[1] == Arcade::GAME_DOWN) {
            _snake[0]->setAsset("librairies/assets/snake/snake/tail_up.png");
            _tmp_directions[0] = Arcade::GAME_DOWN;
        }
        if (_directions[1] == Arcade::GAME_LEFT) {
            _snake[0]->setAsset("librairies/assets/snake/snake/tail_right.png");
            _tmp_directions[0] = Arcade::GAME_LEFT;
        }
        if (_directions[1] == Arcade::GAME_RIGHT) {
            _snake[0]->setAsset("librairies/assets/snake/snake/tail_left.png");
            _tmp_directions[0] = Arcade::GAME_RIGHT;
        }
        _tmp_directions[_snake.size() - 1] = _directions[_snake.size() - 1];
        _directions = _tmp_directions;
    }
    if (is_dead()) {
        _snake.clear();
        _snake.push_back(std::make_shared<Arcade::Object>(22 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/tail_left.png"));
        _snake.push_back(std::make_shared<Arcade::Object>(23 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/body_horizontal.png"));
        _snake.push_back(std::make_shared<Arcade::Object>(24 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/body_horizontal.png"));
        _snake.push_back(std::make_shared<Arcade::Object>(25 , 12 , Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/snake/snake/head_right.png"));
        _directions.clear();
        _directions.push_back(Arcade::GAME_RIGHT);
        _directions.push_back(Arcade::GAME_RIGHT);
        _directions.push_back(Arcade::GAME_RIGHT);
        _directions.push_back(Arcade::GAME_RIGHT);
        return 1;
    }
    return 0;
}

std::vector<std::shared_ptr<Arcade::Object>> snake::Player::get_snake() {
    return _snake;
}

snake::snake()
{
    this->_initMap();
    _apple = std::make_shared<Arcade::Object>(10, 10, Arcade::Type::Rectangle, Arcade::Color::RED, "librairies/assets/snake/apple.png");
    _snake_player = Player();
    _score = std::make_shared<Arcade::Object>(1, 1, Arcade::Type::Text, Arcade::Color::WHITE, "Score : 0");
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
                line.push_back(std::make_shared<Arcade::Object>(j , i , Arcade::Type::Rectangle, Arcade::Color::GREEN,
                                                                "librairies/assets/snake/grass.png"));
            } else {
                line.push_back(std::make_shared<Arcade::Object>(j , i , Arcade::Type::Rectangle, Arcade::Color::BLUE,
                                                                "librairies/assets/snake/grass2.png"));
            }
        }
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
    this->_objects.push_back(_apple);
    this->_score->setAsset("Score : " + std::to_string(_scoreNumber));
    this->_objects.push_back(_score);
}

std::vector<std::shared_ptr<Arcade::Object>> snake::Turn(Arcade::Event event)
{
    if (game_over == 1 && event != Arcade::Event::NEXT_GAME) {
        return this->_objects;
    }
    this->_objects.clear();
    this->_snake_player.set_direction(event);
    if (this->_snake_player.moove_player() == 1) {
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 10, Arcade::Type::Text, Arcade::Color::WHITE, "Game Over"));
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 12, Arcade::Type::Text, Arcade::Color::RED, "Score : " + std::to_string(_scoreNumber)));
        _scoreNumber = 0;
        game_over = 1;
        return this->_objects;
    }
    if (this->_snake_player.he_win()) {
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 10, Arcade::Type::Text, Arcade::Color::WHITE, "You Win"));
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 12, Arcade::Type::Text, Arcade::Color::GREEN, "Score : " + std::to_string(_scoreNumber)));
        _scoreNumber = 0;
        game_over = 1;
        return this->_objects;
    }
    if (this->_snake_player.is_eating(_apple))
        _scoreNumber += 1;
    createObects();

    return this->_objects;
}

int snake::getScore()
{
    return _scoreNumber;
}

extern "C" Arcade::IGame *entryPointGame()
{
    return (new snake());
}