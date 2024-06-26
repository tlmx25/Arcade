/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#ifndef ARCADE_SNAKE_HPP
#define ARCADE_SNAKE_HPP

#include "IGame.hpp"
#include <random>

class snake : public Arcade::IGame {
    class Player {
        public:
            Player();
            int moove_player();
            bool is_eating(std::shared_ptr<Arcade::Object> apple);
            bool is_dead();
            bool he_win();
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
        snake();
        ~snake() override;
        std::vector<std::shared_ptr<Arcade::Object>> Turn(Arcade::Event event) override;
        void init() override {};
        int getScore() override;
    private:
        void createObects();
        std::shared_ptr<Arcade::Object> _apple;
        std::shared_ptr<Arcade::Object> _score;
        std::vector<std::shared_ptr<Arcade::Object>> _objects;
        std::vector<std::vector<std::shared_ptr<Arcade::Object>>> _map;
        void _initMap();
        Player _snake_player;
        int _scoreNumber = 0;
        int game_over = 0;
};

extern "C" Arcade::IGame *entryPointGame();

#endif //ARCADE_SNAKE_HPP
