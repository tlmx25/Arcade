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
        REFRESH,
        NONE,

        IN_A, IN_B, IN_C, IN_D, IN_E, IN_F, IN_G, IN_H, IN_I, IN_J, IN_K, IN_L, IN_M, IN_N, IN_O, IN_P, IN_Q, IN_R, IN_S, IN_T, IN_U, IN_V, IN_W, IN_X, IN_Y, IN_Z,
        IN_0, IN_1, IN_2, IN_3, IN_4, IN_5, IN_6, IN_7, IN_8, IN_9
    };
}
