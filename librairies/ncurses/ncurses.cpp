/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** ncurses
*/

#include "ncurses.hpp"

const std::vector<std::pair<int, Arcade::Event>> keyEvents = {
    {27, Arcade::Event::ESCAPE},
    {KEY_UP, Arcade::Event::GAME_UP},
    {KEY_DOWN, Arcade::Event::GAME_DOWN},
    {KEY_LEFT, Arcade::Event::GAME_LEFT},
    {KEY_RIGHT, Arcade::Event::GAME_RIGHT},
    {' ', Arcade::Event::GAME_SHOOT},
    {KEY_F(1), Arcade::Event::PREV_GAME},
    {KEY_F(2), Arcade::Event::NEXT_GAME},
    {KEY_F(3), Arcade::Event::PREV_LIB},
    {KEY_F(4), Arcade::Event::NEXT_LIB},
    {KEY_F(5), Arcade::Event::GAME_RESTART},
    {KEY_F(8), Arcade::Event::MENU},
    {KEY_F(10), Arcade::Event::REFRESH},
    {'\n', Arcade::Event::ENTER},
    {KEY_BACKSPACE, Arcade::Event::BACKSPACE},
    {'1', Arcade::Event::IN_1},
    {'2', Arcade::Event::IN_2},
    {'3', Arcade::Event::IN_3},
    {'4', Arcade::Event::IN_4},
    {'5', Arcade::Event::IN_5},
    {'6', Arcade::Event::IN_6},
    {'7', Arcade::Event::IN_7},
    {'8', Arcade::Event::IN_8},
    {'9', Arcade::Event::IN_9},
    {'0', Arcade::Event::IN_0},
    {'a', Arcade::Event::IN_A},
    {'b', Arcade::Event::IN_B},
    {'c', Arcade::Event::IN_C},
    {'d', Arcade::Event::IN_D},
    {'e', Arcade::Event::IN_E},
    {'f', Arcade::Event::IN_F},
    {'g', Arcade::Event::IN_G},
    {'h', Arcade::Event::IN_H},
    {'i', Arcade::Event::IN_I},
    {'j', Arcade::Event::IN_J},
    {'k', Arcade::Event::IN_K},
    {'l', Arcade::Event::IN_L},
    {'m', Arcade::Event::IN_M},
    {'n', Arcade::Event::IN_N},
    {'o', Arcade::Event::IN_O},
    {'p', Arcade::Event::IN_P},
    {'q', Arcade::Event::IN_Q},
    {'r', Arcade::Event::IN_R},
    {'s', Arcade::Event::IN_S},
    {'t', Arcade::Event::IN_T},
    {'u', Arcade::Event::IN_U},
    {'v', Arcade::Event::IN_V},
    {'w', Arcade::Event::IN_W},
    {'x', Arcade::Event::IN_X},
    {'y', Arcade::Event::IN_Y},
    {'z', Arcade::Event::IN_Z}
};

/**
 * @brief Construct a new ncurses::ncurses object
*/
Arcade::ncurses::ncurses()
{
    _clock = clock();
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

    refresh();
    for (auto &key : keyEvents) {
        if (ch == key.first)
            return key.second;
    }
    return Arcade::Event::NONE;
}

/**
 * @brief Play the next turn of game
 *
 * @return int
*/
int Arcade::ncurses::playTurn()
{
    clock_t new_clock = clock();
    int time = (new_clock - _clock) / CLOCKS_PER_SEC;

    if (time >= 1) {
        _clock = new_clock;
        return time;
    }
    return 0;
}

/**
 * @brief Define the pair colors
*/
void Arcade::ncurses::define_pair_colors()
{
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_MAGENTA, COLOR_BLACK);
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
        return 1;
    if (color == Arcade::Color::GREEN)
        return 2;
    if (color == Arcade::Color::BLUE)
        return 3;
    if (color == Arcade::Color::YELLOW)
        return 4;
    if (color == Arcade::Color::WHITE)
        return 5;
    if (color == Arcade::Color::BLACK)
        return 6;
    if (color == Arcade::Color::GREY)
        return 7;
    if (color == Arcade::Color::PURPLE)
        return 8;
    return 6;
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
    mvprintw(y, x, "%s", text.c_str());
    attroff(COLOR_PAIR(color));
}

extern "C" Arcade::ncurses *entryPointDisplay()
{
    return new Arcade::ncurses();
}
