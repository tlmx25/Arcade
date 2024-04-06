/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#include "nibbler.hpp"


nibbler::Player::Player()
{
    _snake.push_back(std::make_shared<Arcade::Object>(18, 16, Arcade::Type::Rectangle, Arcade::Color::PURPLE, "librairies/assets/nibbler/green/tail_right.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(19, 16, Arcade::Type::Rectangle, Arcade::Color::PURPLE, "librairies/assets/nibbler/green/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(20, 16, Arcade::Type::Rectangle, Arcade::Color::PURPLE, "librairies/assets/nibbler/green/body_horizontal.png"));
    _snake.push_back(std::make_shared<Arcade::Object>(21, 16, Arcade::Type::Rectangle, Arcade::Color::PURPLE, "librairies/assets/nibbler/green/head_right.png"));

    _directions.push_back(Arcade::GAME_RIGHT);
    _directions.push_back(Arcade::GAME_RIGHT);
    _directions.push_back(Arcade::GAME_RIGHT);
    _directions.push_back(Arcade::GAME_RIGHT);
}

std::vector<std::shared_ptr<Arcade::Object>> nibbler::Player::get_snake()
{
    return _snake;
}

void nibbler::Player::set_direction(Arcade::Event direction)
{
    _direction = direction;
}

Arcade::Event nibbler::Player::get_direction()
{
    return _direction;
}

void nibbler::Player::eat() {
    if (_directions[0] == Arcade::Event::GAME_UP) {
        _snake[0]->setAsset("librairies/assets/nibbler/green/body_straight.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX(), _snake[0]->getPosition().getY() + 1, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/tail.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_UP);
    }
    if (_directions[0] == Arcade::Event::GAME_DOWN) {
        _snake[0]->setAsset("librairies/assets/nibbler/green/body_straight.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX(), _snake[0]->getPosition().getY() - 1, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/tail_down.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_DOWN);
    }
    if (_directions[0] == Arcade::Event::GAME_LEFT) {
        _snake[0]->setAsset("librairies/assets/nibbler/green/body_horizontal.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX() + 1, _snake[0]->getPosition().getY(), Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/tail_left.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_LEFT);
    }
    if (_directions[0] == Arcade::Event::GAME_RIGHT) {
        _snake[0]->setAsset("librairies/assets/nibbler/green/body_horizontal.png");
        _snake.insert(_snake.begin(), std::make_shared<Arcade::Object>(_snake[0]->getPosition().getX() - 1, _snake[0]->getPosition().getY(), Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/tail_right.png"));
        _directions.insert(_directions.begin(), Arcade::GAME_RIGHT);
    }
}

bool nibbler::Player::is_eating(std::vector<std::shared_ptr<Arcade::Object>> *apples)
{
    auto it = apples->begin();
    for (auto &apple : *apples) {
        if (_snake[_snake.size() - 1]->getPosition().getX() == apple->getPosition().getX() &&
            _snake[_snake.size() - 1]->getPosition().getY() == apple->getPosition().getY()) {
            eat();
            apples->erase(it);
            return true;
        }
        it++;
    }
    return false;
}

nibbler::nibbler()
{
    _player = Player();
    initMap(0);
}

nibbler::~nibbler()
{
}

void nibbler::initMap(int level)
{
    int y = 2;

    std::string path = "librairies/assets/nibbler/map" + std::to_string(level) + ".txt";
    std::cout << path << std::endl;
    std::ifstream file(path);

    if (!file) {
        std::cerr << "Unable to open file\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::shared_ptr<Arcade::Object>> row;
        for (size_t x = 0; x < line.size(); x++) {
            if (line[x] == '0') {
                row.push_back(std::make_shared<Arcade::Object>(x + 14, y, Arcade::Type::Rectangle, Arcade::Color::WHITE));
            }
            if (line[x] == '1') {
                row.push_back(std::make_shared<Arcade::Object>(x + 14, y, Arcade::Type::Rectangle, Arcade::Color::GREEN,
                                                               "librairies/assets/nibbler/wall.png"));
            }
            if (line[x] == '2') {
                _apples.push_back(std::make_shared<Arcade::Object>(x + 14, y, Arcade::Type::Rectangle, Arcade::Color::RED,
                                                                  "librairies/assets/nibbler/food-4.png"));
                row.push_back(std::make_shared<Arcade::Object>(x + 14, y, Arcade::Type::Rectangle, Arcade::Color::WHITE));
            }
        }
        _map.push_back(row);
        y++;
    }

    file.close();

    return;
}

bool nibbler::Player::is_dead()
{
    size_t size = _snake.size() - 1;
    for (size_t i = 0; i < _snake.size() - 2; i++) {
        if (_snake[size]->getPosition().getX() == _snake[i]->getPosition().getX() && _snake[size]->getPosition().getY() == _snake[i]->getPosition().getY()) {
            return true;
        }
    }
    return false;
}

void nibbler::init() {
    std::cout << "Nibbler init" << std::endl;
}

int nibbler::getScore()
{
    return _scoreNumber;
}

Arcade::Event nibbler::Player::is_colliding(int x, int y, std::vector<std::vector<std::shared_ptr<Arcade::Object>>> map, std::shared_ptr<Arcade::Object> obj)
{
    size_t size = _snake.size() - 1;
    int xtmp = _snake[size]->getPosition().getX() - x;
    int ytmp = _snake[size]->getPosition().getY() - y;

    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j]->getPosition().getX() == x && map[i][j]->getPosition().getY() == y && map[i][j]->getAsset() == "librairies/assets/nibbler/wall.png") {
                if (_directions[size] == Arcade::GAME_UP) {
                    if (map[i + ytmp][j + xtmp + 1]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_LEFT;
                    }
                    if (map[i + ytmp][j + xtmp - 1]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_RIGHT;
                    }
                    return Arcade::GAME_UP;
                }
                if (_directions[size] == Arcade::GAME_DOWN) {
                    if (map[i + ytmp][j + xtmp + 1]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_RIGHT;
                    }
                    if (map[i + ytmp][j + xtmp - 1]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_LEFT;
                    }
                    return Arcade::GAME_UP;
                }
                if (_directions[size] == Arcade::GAME_LEFT) {
                    if (map[i + ytmp + 1][j + xtmp]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_RIGHT;
                    }
                    if (map[i + ytmp - 1][j + xtmp]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_LEFT;
                    }
                    return Arcade::GAME_UP;
                }
                if (_directions[size] == Arcade::GAME_RIGHT) {
                    if (map[i + ytmp + 1][j + xtmp]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_LEFT;
                    }
                    if (map[i + ytmp - 1][j + xtmp]->getColor() == Arcade::Color::GREEN) {
                        return Arcade::GAME_RIGHT;
                    }
                    return Arcade::GAME_UP;
                }
            }
        }
    }
    return Arcade::NONE;
}

bool nibbler::Player::side_colide(int x, int y, std::vector<std::vector<std::shared_ptr<Arcade::Object>>> map) {
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j]->getPosition().getX() == x && map[i][j]->getPosition().getY() == y && map[i][j]->getColor() == Arcade::Color::GREEN) {
                return true;
            }
        }
    }
    return false;
}

int nibbler::Player::moove_player(std::vector<std::vector<std::shared_ptr<Arcade::Object>>> map) {
    int x, y, x_tmp, y_tmp = 0;
    bool check = false;
    bool is_collide = false;
    std::shared_ptr<Arcade::Object> tmp;
    std::vector<Arcade::Event> _tmp_directions = _directions;
    Arcade::Event direction;

    if (get_direction() == Arcade::NONE) {
        for (size_t i = _snake.size() - 1; i != 0; i--) {
            if (i + 1 == _snake.size()) {
                x = _snake[i]->getPosition().getX();
                y = _snake[i]->getPosition().getY();
                if (_directions[i] == Arcade::GAME_UP) {
                    direction = is_colliding(x, y - 1, map, _snake[i]);
                    if (direction != Arcade::NONE) {
                        set_direction(direction);
                        is_collide = true;
                        break;
                    }
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head.png");
                    _snake[i]->setPosition(x, y - 1);
                } else if (_directions[i] == Arcade::GAME_DOWN) {
                    direction = is_colliding(x, y + 1, map, _snake[i]);
                    if (direction != Arcade::NONE) {
                        set_direction(direction);
                        is_collide = true;
                        break;
                    }
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_down.png");
                    _snake[i]->setPosition(x, y + 1);
                } else if (_directions[i] == Arcade::GAME_LEFT) {
                    direction = is_colliding(x - 1, y, map, _snake[i]);
                    if (direction != Arcade::NONE) {
                        set_direction(direction);
                        is_collide = true;
                        break;
                    }
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_left.png");
                    _snake[i]->setPosition(x - 1, y);
                } else {
                    direction = is_colliding(x + 1, y, map, _snake[i]);
                    if (direction != Arcade::NONE) {
                        set_direction(direction);
                        is_collide = true;
                        break;
                    }
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_right.png");
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
        if (!is_collide) {
            _snake[0]->setPosition(x, y);
            check = true;
        } else if (get_direction() == Arcade::GAME_UP) {
            return 0;
        }
    }

    if (get_direction() == Arcade::GAME_LEFT && !check) {
        for (size_t i = _snake.size() - 1; i != 0; i--) {
            if (i + 1 == _snake.size()) {
                x = _snake[i]->getPosition().getX();
                y = _snake[i]->getPosition().getY();
                if (_directions[i] == Arcade::GAME_UP) {
                    if (side_colide(x - 1, y, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_LEFT;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_left.png");
                    _snake[i]->setPosition(x - 1, y);
                } else if (_directions[i] == Arcade::GAME_DOWN) {
                    if (side_colide(x + 1, y, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_right.png");
                    _snake[i]->setPosition(x + 1, y);
                } else if (_directions[i] == Arcade::GAME_LEFT) {
                    if (side_colide(x, y + 1, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_DOWN;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_down.png");
                    _snake[i]->setPosition(x, y + 1);
                } else {
                    if (side_colide(x, y - 1, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_UP;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head.png");
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
                    if (side_colide(x + 1, y, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_RIGHT;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_right.png");
                    _snake[i]->setPosition(x + 1, y);
                } else if (_directions[i] == Arcade::GAME_DOWN) {
                    if (side_colide(x - 1, y, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_LEFT;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_left.png");
                    _snake[i]->setPosition(x - 1, y);
                } else if (_directions[i] == Arcade::GAME_LEFT) {
                    if (side_colide(x, y - 1, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_UP;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head.png");
                    _snake[i]->setPosition(x, y - 1);
                } else {
                    if (side_colide(x, y + 1, map)) {
                        return 0;
                    }
                    _directions[i] = Arcade::GAME_DOWN;
                    _snake[i]->setAsset("librairies/assets/nibbler/green/head_down.png");
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
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_straight.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_downright.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == -1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_downleft.png");
                }
                _tmp_directions[i] = Arcade::GAME_UP;
            }
            if (_directions[i + 1] == Arcade::GAME_DOWN) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == -1)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_straight.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_upright.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == -1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_upleft.png");
                }
                _tmp_directions[i] = Arcade::GAME_DOWN;
            }
            if (_directions[i + 1] == Arcade::GAME_LEFT) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_horizontal.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 1)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_upleft.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == -1)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_downleft.png");
                }
                _tmp_directions[i] = Arcade::GAME_LEFT;
            }
            if (_directions[i + 1] == Arcade::GAME_RIGHT) {
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == -1) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 0)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_horizontal.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == 1)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_upright.png");
                }
                if ((_snake[i - 1]->getPosition().getX() - _snake[i]->getPosition().getX() == 0) &&
                    (_snake[i - 1]->getPosition().getY() - _snake[i]->getPosition().getY() == -1)) {
                    _snake[i]->setAsset("librairies/assets/nibbler/green/body_turn_downright.png");
                }
                _tmp_directions[i] = Arcade::GAME_RIGHT;
            }
        }
        if (_directions[1] == Arcade::GAME_UP) {
            _snake[0]->setAsset("librairies/assets/nibbler/green/tail.png");
            _tmp_directions[0] = Arcade::GAME_UP;
        }
        if (_directions[1] == Arcade::GAME_DOWN) {
            _snake[0]->setAsset("librairies/assets/nibbler/green/tail_down.png");
            _tmp_directions[0] = Arcade::GAME_DOWN;
        }
        if (_directions[1] == Arcade::GAME_LEFT) {
            _snake[0]->setAsset("librairies/assets/nibbler/green/tail_left.png");
            _tmp_directions[0] = Arcade::GAME_LEFT;
        }
        if (_directions[1] == Arcade::GAME_RIGHT) {
            _snake[0]->setAsset("librairies/assets/nibbler/green/tail_right.png");
            _tmp_directions[0] = Arcade::GAME_RIGHT;
        }
        _tmp_directions[_snake.size() - 1] = _directions[_snake.size() - 1];
        _directions = _tmp_directions;
    }
    if (is_dead()) {
        _snake.clear();
        _snake.push_back(std::make_shared<Arcade::Object>(18, 16, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/tail_right.png"));
        _snake.push_back(std::make_shared<Arcade::Object>(19, 16, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/body_horizontal.png"));
        _snake.push_back(std::make_shared<Arcade::Object>(20, 16, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/body_horizontal.png"));
        _snake.push_back(std::make_shared<Arcade::Object>(21, 16, Arcade::Type::Rectangle, Arcade::Color::GREEN, "librairies/assets/nibbler/green/head_right.png"));
        _directions.clear();
        _directions.push_back(Arcade::GAME_RIGHT);
        _directions.push_back(Arcade::GAME_RIGHT);
        _directions.push_back(Arcade::GAME_RIGHT);
        _directions.push_back(Arcade::GAME_RIGHT);
        return 1;
    }
    return 0;
}

bool nibbler::he_win()
{
    if (_apples.empty()) {
        return true;
    }
    return false;
}

void nibbler::createObects()
{
    for (auto &line : this->_map) {
        for (auto &obj : line) {
            this->_objects.push_back(obj);
        }
    }
    for (auto &obj : _apples) {
        this->_objects.push_back(obj);
    }
    for (auto &obj : _player.get_snake()) {
        this->_objects.push_back(obj);
    }
    this->_objects.push_back(std::make_shared<Arcade::Object>(0, 0, Arcade::Type::Text, Arcade::Color::WHITE, "Score : " + std::to_string(_scoreNumber)));
}

std::vector<std::shared_ptr<Arcade::Object>> nibbler::Turn(Arcade::Event event)
{
    std::cout << "Nibbler event" << event << std::endl;
    if (game_over == 2 && event == Arcade::Event::ENTER) {
        _map.clear();
        _apples.clear();
        level += 1;
        if (level == 3) {
            _objects.clear();
            _objects.push_back(std::make_shared<Arcade::Object>(21, 10, Arcade::Type::Text, Arcade::Color::WHITE, "You win"));
            _objects.push_back(std::make_shared<Arcade::Object>(21, 12, Arcade::Type::Text, Arcade::Color::WHITE, "Press F5 to restart the game"));
            game_over = 1;
            level = 0;
            initMap(level);
            return this->_objects;
        }
        initMap(level);
        game_over = 0;
        _player = Player();
    }
    if (game_over == 2 && event != Arcade::Event::GAME_RESTART) {
        _objects.push_back(std::make_shared<Arcade::Object>(21, 13, Arcade::Type::Text, Arcade::Color::WHITE, "Press Enter to continue Or F5 to restart the game"));
        return this->_objects;
    }
    if (game_over == 1 && event != Arcade::Event::GAME_RESTART) {
        return this->_objects;
    }

    game_over = 0;
    this->_objects.clear();
    _player.set_direction(event);
    if (_player.moove_player(_map) == 1) {
        _map.clear();
        _apples.clear();
        initMap(level);
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 10, Arcade::Type::Text, Arcade::Color::WHITE, "Game Over"));
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 12, Arcade::Type::Text, Arcade::Color::RED, "Score : " + std::to_string(_scoreNumber)));
        _scoreNumber = 0;
        game_over = 1;
        return this->_objects;
    }
    if (he_win()) {
        _map.clear();
        _apples.clear();
        initMap(level);
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 10, Arcade::Type::Text, Arcade::Color::WHITE, "You win"));
        this->_objects.push_back(std::make_shared<Arcade::Object>(21, 12, Arcade::Type::Text, Arcade::Color::GREEN, "Score : " + std::to_string(_scoreNumber)));
        _scoreNumber = 0;
        game_over = 2;
        return this->_objects;
    }
    if (this->_player.is_eating(&_apples))
        _scoreNumber += 1;
    createObects();
    return _objects;
}

extern "C" Arcade::IGame *entryPointGame()
{
    return (new nibbler());
}