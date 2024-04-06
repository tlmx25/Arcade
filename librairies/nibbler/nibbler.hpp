/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** nibbler
*/

#ifndef ARCADE_NIBBLER_HPP
#define ARCADE_NIBBLER_HPP

#include "IGame.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>

class nibbler : public Arcade::IGame{
    class Player {
        public:
            Player();
            int moove_player(std::vector<std::vector<std::shared_ptr<Arcade::Object>>> map);
            bool is_eating(std::vector<std::shared_ptr<Arcade::Object>> *apples);
            bool is_dead();
            Arcade::Event is_colliding(int x, int y, std::vector<std::vector<std::shared_ptr<Arcade::Object>>> map, std::shared_ptr<Arcade::Object> obj);
            bool side_colide(int x, int y, std::vector<std::vector<std::shared_ptr<Arcade::Object>>> map);
            void eat();
            std::vector<std::shared_ptr<Arcade::Object>> get_snake();
            void set_direction(Arcade::Event direction);
            Arcade::Event get_direction();
        private:
            std::vector<std::shared_ptr<Arcade::Object>> _snake;
            std::vector<Arcade::Event> _directions;
            Arcade::Event _direction = Arcade::GAME_RIGHT;
    };
    public:
        nibbler();
        ~nibbler() override;
        std::vector<std::shared_ptr<Arcade::Object>> Turn(Arcade::Event event) override;
        void init() override;
        int getScore() override;
        bool he_win();
    private:
        void createObects();
        std::vector<std::shared_ptr<Arcade::Object>> _apples;
        std::shared_ptr<Arcade::Object> _score;
        std::vector<std::shared_ptr<Arcade::Object>> _objects;
        std::vector<std::vector<std::shared_ptr<Arcade::Object>>> _map;
        Player _player;
        void initMap(int level);
        int _scoreNumber = 0;
        int game_over = 0;
        int level = 0;
};

extern "C" Arcade::IGame *entryPointGame();
#endif //ARCADE_NIBBLER_HPP
