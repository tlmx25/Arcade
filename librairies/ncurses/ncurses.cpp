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
    _clock = clock();
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
        drawCircle(object);
    else if (object->getType() == Arcade::Type::Rectangle)
        drawRectangle(object);
    else if (object->getType() == Arcade::Type::Text)
        drawText(object);
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
    // TODO
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

/**
 * @brief Get the color
 *
 * @param color
 * @return int
*/
int Arcade::ncurses::_getColor(Arcade::Color color)
{
    if (color == Arcade::Color::RED)
        return 2;
    if (color == Arcade::Color::GREEN)
        return 3;
    if (color == Arcade::Color::BLUE)
        return 5;
    if (color == Arcade::Color::YELLOW)
        return 4;
    if (color == Arcade::Color::WHITE)
        return 1;
    if (color == Arcade::Color::BLACK)
        return 0;
    return 0;
}

/**
 * @brief Draw a circle
 *
 * @param object
*/
void Arcade::ncurses::drawCircle(const std::shared_ptr<Arcade::Object> object)
{
    int color = _getColor(object->getColor());
    int x = object->getPosition().getX();
    int y = object->getPosition().getY();
    int radius = OBJECT_SIZE / 2;

    attron(COLOR_PAIR(color));
    for (int i = 0; i < 360; i++) {
        int x1 = x + radius * cos(i * M_PI / 180);
        int y1 = y + radius * sin(i * M_PI / 180);
        mvprintw(y1, x1, " ");
    }
    attroff(COLOR_PAIR(color));
}

/**
 * @brief Draw a rectangle
 *
 * @param object
*/
void Arcade::ncurses::drawRectangle(const std::shared_ptr<Arcade::Object> object)
{
    int color = _getColor(object->getColor());
    int x = object->getPosition().getX();
    int y = object->getPosition().getY();
    int width = OBJECT_SIZE;
    int height = OBJECT_SIZE;

    attron(COLOR_PAIR(color));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            mvprintw(y + j, x + i, " ");
        }
    }
    attroff(COLOR_PAIR(color));
}

/**
 * @brief Draw a text
 *
 * @param object
*/
void Arcade::ncurses::drawText(const std::shared_ptr<Arcade::Object> object)
{
    int color = _getColor(object->getColor());
    int x = object->getPosition().getX();
    int y = object->getPosition().getY();
    std::string text = object->getAsset();

    attron(COLOR_PAIR(color));
    mvprintw(y, x, text.c_str());
    attroff(COLOR_PAIR(color));
}
