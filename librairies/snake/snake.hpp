/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** snake
*/

#ifndef ARCADE_SNAKE_HPP
#define ARCADE_SNAKE_HPP

#include "IGame.hpp"

class snake : public Arcade::IGame {
    class Player {
        public:
            Player();
            void moove_player();
            bool is_eating();
            bool is_dead();
            std::vector<std::shared_ptr<Arcade::Object>> get_snake();
            void set_direction(Arcade::Event direction);
            Arcade::Event get_direction();
            Arcade::Event get_last_direction();
            void set_last_direction(Arcade::Event direction);
        private:
            std::vector<std::shared_ptr<Arcade::Object>> _snake;
            std::vector<Arcade::Event> _directions;
            Arcade::Event _direction = Arcade::GAME_RIGHT;
            Arcade::Event _last_direction = Arcade::NONE;
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
        std::vector<std::shared_ptr<Arcade::Object>> _objects;
        std::vector<std::vector<std::shared_ptr<Arcade::Object>>> _map;
        void _initMap();
        Player _snake_player;
};

extern "C" Arcade::IGame *entryPointGame();

#endif //ARCADE_SNAKE_HPP
