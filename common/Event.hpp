/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Input
*/

#pragma once

/**
 * @file Event.hpp
 * @brief Event enumeration for the Arcade project
 */

namespace Arcade {

    /**
     * @enum Event
     * @brief An enumeration to standardize events across libraries.
     *
     * This enumeration contains all possible event that can be used in the Arcade project.
     * It includes all the events that can be triggered by the user.
     */
    enum Event {
        GAME_UP, ///< Represents the 'UP' key
        GAME_DOWN, ///< Represents the 'DOWN' key
        GAME_LEFT, ///< Represents the 'LEFT' key
        GAME_RIGHT, ///< Represents the 'RIGHT' key
        ESCAPE, ///< Represents the 'ESCAPE' key
        SPACE, ///< Represents the 'SPACE' key
        GAME_RESTART, ///< Represents the 'RESTART' key
        ENTER, ///< Represents the 'ENTER' key
        BACKSPACE, ///< Represents the 'BACKSPACE' key
        PREV_GAME, ///< Represents the 'PREV_GAME' key
        NEXT_GAME, ///< Represents the 'NEXT_GAME' key
        PREV_LIB, ///< Represents the 'PREV_LIB' key
        NEXT_LIB, ///< Represents the 'NEXT_LIB' key
        MENU, ///< Represents the 'MENU' key
        GAME_SHOOT,
        REFRESH, ///< Represents the 'REFRESH' key
        NONE, ///< Represents no key
        IN_1, ///< Represents the '1' key
        IN_2, ///< Represents the '2' key
        IN_3, ///< Represents the '3' key
        IN_4, ///< Represents the '4' key
        IN_5, ///< Represents the '5' key
        IN_6, ///< Represents the '6' key
        IN_7, ///< Represents the '7' key
        IN_8, ///< Represents the '8' key
        IN_9, ///< Represents the '9' key
        IN_0, ///< Represents the '0' key
        IN_A, ///< Represents the 'A' key
        IN_B, ///< Represents the 'B' key
        IN_C, ///< Represents the 'C' key
        IN_D, ///< Represents the 'D' key
        IN_E, ///< Represents the 'E' key
        IN_F, ///< Represents the 'F' key
        IN_G, ///< Represents the 'G' key
        IN_H, ///< Represents the 'H' key
        IN_I, ///< Represents the 'I' key
        IN_J, ///< Represents the 'J' key
        IN_K, ///< Represents the 'K' key
        IN_L, ///< Represents the 'L' key
        IN_M, ///< Represents the 'M' key
        IN_N, ///< Represents the 'N' key
        IN_O, ///< Represents the 'O' key
        IN_P, ///< Represents the 'P' key
        IN_Q, ///< Represents the 'Q' key
        IN_R, ///< Represents the 'R' key
        IN_S, ///< Represents the 'S' key
        IN_T, ///< Represents the 'T' key
        IN_U, ///< Represents the 'U' key
        IN_V, ///< Represents the 'V' key
        IN_W, ///< Represents the 'W' key
        IN_X, ///< Represents the 'X' key
        IN_Y, ///< Represents the 'Y' key
        IN_Z, ///< Represents the 'Z' key
    };
}
