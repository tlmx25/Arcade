/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ncurses
*/

#include "ncurses.hpp"

/**
 * @brief Construct a new ncurses::ncurses object
*/
Arcade::ncurses::ncurses()
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    define_pair_colors();
    curs_set(0);
    refresh();
}

/**
 * @brief Destroy the ncurses::ncurses object
*/
Arcade::ncurses::~ncurses()
{
    endwin();
}

/**
 * @brief Clear the window
*/
void Arcade::ncurses::clearWindow()
{
    wclear(stdscr);
}

/**
 * @brief Update the window
*/
void Arcade::ncurses::updateWindow()
{
    wrefresh(stdscr);
}

/**
 * @brief Draw an object
 *
 * @param object
*/
void Arcade::ncurses::draw(std::shared_ptr<Arcade::Object> object)
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
Arcade::Event Arcade::ncurses::getInput()
{
    int ch = getch();

    // refresh();
    if (ch == 27)
        return Arcade::Event::ESCAPE;
    if (ch == KEY_UP)
        return Arcade::Event::GAME_UP;
    if (ch == KEY_DOWN)
        return Arcade::Event::GAME_DOWN;
    if (ch == KEY_LEFT)
        return Arcade::Event::GAME_LEFT;
    if (ch == KEY_RIGHT)
        return Arcade::Event::GAME_RIGHT;
    if (ch == 32)
        return Arcade::Event::GAME_SHOOT;
    if (ch == '\n')
        return Arcade::Event::ENTER;
    if (ch == KEY_BACKSPACE)
        return Arcade::Event::BACKSPACE;
    if (ch == KEY_F(1))
        return Arcade::Event::PREV_GAME;
    if (ch == KEY_F(2))
        return Arcade::Event::NEXT_GAME;
    if (ch == KEY_F(3))
        return Arcade::Event::PREV_LIB;
    if (ch == KEY_F(4))
        return Arcade::Event::NEXT_LIB;
    if (ch == KEY_F(5))
        return Arcade::Event::GAME_RESTART;
    if (ch == KEY_F(8))
        return Arcade::Event::MENU;
    if (ch == KEY_F(10))
        return Arcade::Event::REFRESH;
    return Arcade::Event::NONE;
}

/**
 * @brief Play the next turn of game
 *
 * @return int
*/
int Arcade::ncurses::playTurn()
{
    // TODO: Implement this method
    return 0;
}

/**
 * @brief Define the pair colors
*/
void Arcade::ncurses::define_pair_colors()
{
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_BLACK, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    // TODO: Add more colors
}
