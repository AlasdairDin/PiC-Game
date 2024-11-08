/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <drawcontext.hpp>

namespace uwe {
    // event types
    enum class Event {
        EVENT_QUIT = SDL_QUIT,
        EVENT_KEYDOWN = SDL_KEYDOWN,
    };

    // scancodes
    enum class Scancode {
        SCANCODE_0 = SDL_SCANCODE_0,
        SCANCODE_1 = SDL_SCANCODE_1,
        SCANCODE_2 = SDL_SCANCODE_2,
        SCANCODE_3 = SDL_SCANCODE_3,
        SCANCODE_4 = SDL_SCANCODE_4,
        SCANCODE_5 = SDL_SCANCODE_5,
        SCANCODE_6 = SDL_SCANCODE_6,
        SCANCODE_7 = SDL_SCANCODE_7,
        SCANCODE_8 = SDL_SCANCODE_8,
        SCANCODE_9 = SDL_SCANCODE_9,

        SCANCODE_A = SDL_SCANCODE_A,
        SCANCODE_B = SDL_SCANCODE_B,
        SCANCODE_C = SDL_SCANCODE_C,
        SCANCODE_D = SDL_SCANCODE_D,
        SCANCODE_E = SDL_SCANCODE_E,
        SCANCODE_F = SDL_SCANCODE_F,
        SCANCODE_G = SDL_SCANCODE_G,
        SCANCODE_H = SDL_SCANCODE_H,
        SCANCODE_I = SDL_SCANCODE_I,
        SCANCODE_J = SDL_SCANCODE_J,
        SCANCODE_K = SDL_SCANCODE_K,
        SCANCODE_L = SDL_SCANCODE_L,
        SCANCODE_M = SDL_SCANCODE_M,
        SCANCODE_N = SDL_SCANCODE_N,
        SCANCODE_O = SDL_SCANCODE_O,
        SCANCODE_P = SDL_SCANCODE_P,
        SCANCODE_Q = SDL_SCANCODE_Q,
        SCANCODE_R = SDL_SCANCODE_R,
        SCANCODE_S = SDL_SCANCODE_S,
        SCANCODE_T = SDL_SCANCODE_T,
        SCANCODE_U = SDL_SCANCODE_U,
        SCANCODE_V = SDL_SCANCODE_V,
        SCANCODE_W = SDL_SCANCODE_W,
        SCANCODE_X = SDL_SCANCODE_X,
        SCANCODE_Y = SDL_SCANCODE_Y,
        SCANCODE_Z = SDL_SCANCODE_Z,    

        SCANCODE_LSHIFT = SDL_SCANCODE_LSHIFT,
        SCANCODE_RSHIFT = SDL_SCANCODE_RSHIFT,
        SCANCODE_RETURN = SDL_SCANCODE_RETURN,
        SCANCODE_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        SCANCODE_SPACE = SDL_SCANCODE_SPACE,

        SCANCODE_UP = SDL_SCANCODE_UP,
        SCANCODE_DOWN = SDL_SCANCODE_DOWN,
        SCANCODE_LEFT = SDL_SCANCODE_LEFT,
        SCANCODE_RIGHT = SDL_SCANCODE_RIGHT,
    };

    class Context {
    public:
        /** @brief Create a context
         * @param width an integer setting the window width
         * @param height an integer setting the window height
         */
        Context(int width, int height);

        /// Destory context
        ~Context();

        /// Output details of GPU backend and texture formats
        void dump_renderer_info();

        /// run the control loop, returns only when user exits
        void run();
    private:
        int height_;                ///< window height
        int width_;                 ///< window width
        int tex_width_;             ///< texture width
        int tex_height_;            ///< texture height
        SDL_Window* window_;        ///< window handle
        SDL_Renderer* renderer_;    ///< graphics backend handle
        SDL_Texture* texture_;      ///< pixel buffer texture handle

        std::vector< uint8_t > pixels_; ///< pixels representing framebuffer
    };
}

