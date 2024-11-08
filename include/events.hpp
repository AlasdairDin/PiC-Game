/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <vector>

#include <SDL2/SDL.h>

namespace uwe {

    // event types
    enum class Event {
        EVENT_QUIT = SDL_QUIT,
        EVENT_KEYDOWN = SDL_KEYDOWN,
    };

    // scancodes
    enum class Scancode {
        D_0 = SDL_SCANCODE_0,
        D_1 = SDL_SCANCODE_1,
        D_2 = SDL_SCANCODE_2,
        D_3 = SDL_SCANCODE_3,
        D_4 = SDL_SCANCODE_4,
        D_5 = SDL_SCANCODE_5,
        D_6 = SDL_SCANCODE_6,
        D_7 = SDL_SCANCODE_7,
        D_8 = SDL_SCANCODE_8,
        D_9 = SDL_SCANCODE_9,

        A = SDL_SCANCODE_A,
        B = SDL_SCANCODE_B,
        C = SDL_SCANCODE_C,
        D = SDL_SCANCODE_D,
        E = SDL_SCANCODE_E,
        F = SDL_SCANCODE_F,
        G = SDL_SCANCODE_G,
        H = SDL_SCANCODE_H,
        I = SDL_SCANCODE_I,
        J = SDL_SCANCODE_J,
        K = SDL_SCANCODE_K,
        L = SDL_SCANCODE_L,
        M = SDL_SCANCODE_M,
        N = SDL_SCANCODE_N,
        O = SDL_SCANCODE_O,
        P = SDL_SCANCODE_P,
        Q = SDL_SCANCODE_Q,
        R = SDL_SCANCODE_R,
        S = SDL_SCANCODE_S,
        T = SDL_SCANCODE_T,
        U = SDL_SCANCODE_U,
        V = SDL_SCANCODE_V,
        W = SDL_SCANCODE_W,
        X = SDL_SCANCODE_X,
        Y = SDL_SCANCODE_Y,
        Z = SDL_SCANCODE_Z,    

        LSHIFT = SDL_SCANCODE_LSHIFT,
        RSHIFT = SDL_SCANCODE_RSHIFT,
        RETURN = SDL_SCANCODE_RETURN,
        BACKSPACE = SDL_SCANCODE_BACKSPACE,
        SPACE = SDL_SCANCODE_SPACE,

        UP = SDL_SCANCODE_UP,
        DOWN = SDL_SCANCODE_DOWN,
        LEFT = SDL_SCANCODE_LEFT,
        RIGHT = SDL_SCANCODE_RIGHT,
    };

    enum class Button {
        LEFT = SDL_BUTTON_LEFT,
        RIGHT = SDL_BUTTON_RIGHT,
    };

} // namespace uwe