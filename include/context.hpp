/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_FontCache.h>

#include <events.hpp>

namespace uwe {
    class Colour {
    public:
        uint8_t blue_;
        uint8_t green_;
        uint8_t red_;
        uint8_t alpha_;

        Colour(uint8_t red, uint8_t green,  uint8_t  blue, uint8_t alpha):
            red_{red},
            green_{green},
            blue_{blue},
            alpha_{alpha} {
        }

        Colour(const Colour& colour) : 
           red_{colour.red_},
            green_{colour.green_},
            blue_{colour.blue_},
            alpha_{colour.alpha_}  { }

        static Colour red() {
            return Colour{ 255, 0, 0, SDL_ALPHA_OPAQUE };
        }

        static Colour green() {
            return Colour{ 0, 255, 0, SDL_ALPHA_OPAQUE };
        }

        static Colour blue() {
            return Colour{ 0, 0, 255, SDL_ALPHA_OPAQUE };
        }

        static Colour white() {
            return Colour{ 255, 255, 255, SDL_ALPHA_OPAQUE };
        }

        static Colour black() {
            return Colour{ 0, 0, 0, SDL_ALPHA_OPAQUE };
        }
    };

    inline Colour make_colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
        return Colour{red, green, blue, alpha};
    }

    typedef SDL_Rect Rect;

    inline Rect make_rect(int x, int y, int width, int height) {
        Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
        return rect;
    }

    typedef SDL_Texture* Image;

    typedef FC_Font* Font;

    class Context {
    public:
        /** @brief Create a context
         * @param width an integer setting the window width
         * @param height an integer setting the window height
         */
        Context();

        /// Destory context
        ~Context();

        void init(int width, int height, std::string title);

        /// Output details of GPU backend and texture formats
        void dump_renderer_info();

        /// run the control loop, returns only when user exits
        //void run(App* app);

        int get_height() const {
            return height_;
        }

        int get_width() const {
            return width_;
        }

        SDL_Window* get_window() const {
            return window_;
        }

        SDL_Renderer* get_renderer() const {
            return renderer_;
        }

        SDL_Texture* get_texture() const {
            return texture_;
        }

        std::vector< uint8_t >& get_pixels() {
            return pixels_;
        }

        uint8_t& pixel(size_t offset) {
            return pixels_[offset];
        }

        void set_pixel(size_t offset, Colour colour) {
            pixels_[offset + 0] = colour.blue_;
            pixels_[offset + 1] = colour.green_;
            pixels_[offset + 2] = colour.red_;
            pixels_[offset + 3] = colour.alpha_;
        }

        int get_tex_width() const {
            return tex_width_;
        }

        int get_tex_height() const {
            return tex_height_;
        }

        Image create_image(std::string path) {
            SDL_Surface* surface = IMG_Load(path.c_str()); 
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface); 
            SDL_FreeSurface(surface);
            return texture;
        }

        Image create_image(int tex_width, int tex_height) {
            return SDL_CreateTexture(
                renderer_, 
                SDL_PIXELFORMAT_RGBA8888, 
                SDL_TEXTUREACCESS_TARGET,
                tex_width,
                tex_height);
        }

        void delete_image(Image image) {
            SDL_DestroyTexture(image);
        }

        void get_image_size(Image image, int *width, int *height) {
            uint32_t format;
            int access;
            SDL_QueryTexture(image, &format, &access, width, height);
        }

        void draw_image(Image image, Rect src, Rect dest) {
            SDL_RenderCopy(renderer_, image, &src, &dest);
        }

        Font create_font(std::string path, int point_size, Colour colour) {
            auto font = FC_CreateFont();
            FC_LoadFont(
                font, 
                renderer_, 
                path.c_str(), 
                point_size, 
                FC_MakeColor(colour.red_, colour.green_, colour.blue_, colour.alpha_), 
                TTF_STYLE_NORMAL);
            loaded_fonts_.push_back(font);
            return font;
        }

        void draw_font(Font font, std::string msg, float x, float y) {
            FC_Draw(font, renderer_, x, y, msg.c_str()); 
        }

    private:
        int height_;                ///< window height
        int width_;                 ///< window width
        int tex_width_;             ///< texture width
        int tex_height_;            ///< texture height
        SDL_Window* window_;        ///< window handle
        SDL_Renderer* renderer_;    ///< graphics backend handle
        SDL_Texture* texture_;      ///< pixel buffer texture handle

        std::vector< uint8_t > pixels_; ///< pixels representing framebuffer
        std::vector<Font> loaded_fonts_;
    };
}

