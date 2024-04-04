/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#include "nibbler.hpp"
nibbler::nibbler()
{
    initMap();
}
nibbler::~nibbler()
{
}

void nibbler::initMap()
{
    int y = 2;
    std::ifstream file("librairies/assets/nibbler/map1.txt");

    if (!file) {
        std::cerr << "Unable to open file\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::shared_ptr<Arcade::Object>> row;
        for (size_t x = 0; x < line.size(); x++) {
            if (line[x] == '0') {
                row.push_back(std::make_shared<Arcade::Object>(x + 14, y, Arcade::Type::Rectangle, Arcade::Color::BLACK, "librairies/assets/nibbler/floor_tyles.png"));
            }
            if (line[x] == '1') {
                row.push_back(std::make_shared<Arcade::Object>(x + 14, y, Arcade::Type::Rectangle, Arcade::Color::RED,
                                                               "librairies/assets/nibbler/wall.png"));
            }
        }
        _map.push_back(row);
        y++;
    }

    file.close();
    return;
}

void nibbler::init() {
    std::cout << "Nibbler init" << std::endl;
}

int nibbler::getScore()
{
    return 0;
}

void nibbler::createObects()
{
    for (auto &line : this->_map) {
        for (auto &obj : line) {
            this->_objects.push_back(obj);
        }
    }
}

std::vector<std::shared_ptr<Arcade::Object>> nibbler::Turn(Arcade::Event event)
{
    createObects();
    return _objects;
}

extern "C" Arcade::IGame *entryPointGame()
{
    return (new nibbler());
}