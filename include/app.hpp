/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <events.hpp>
#include <context.hpp>

namespace uwe {

    class App {
    private:
        Context context_;

        bool output_framerate_;
    public:
        App();
        ~App();

        void init(int width, int height, std::string title);
        void run();

        /// toggles output framerate to console
        void toggle_framerate() {
            output_framerate_ = !output_framerate_;
        }

        virtual void begin() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void key_pressed(Scancode scancode, bool is_repeat) {

        };

        virtual void key_released(Scancode scancode) {
            
        };

        virtual void mouse_pressed(int x, int y, Button button) {

        };

        virtual void mouse_released(int x, int y, Button button) {
            
        };

        virtual void mouse_moved(int x, int y) {
            
        };

        // API

        int get_framebuffer_width() const {
            return context_.get_tex_width();
        }

        int get_framebuffer_height() const {
            return context_.get_tex_height();
        }

        uint8_t& framebuffer(size_t offset) {
            return context_.pixel(offset);
        }

        void set_framebuffer_non_scaled(size_t offset, Colour colour) {
            context_.set_pixel(offset, colour);
        }

        void set_framebuffer(int x, int y, Colour colour) {
             int offset = x*sizeof(uwe::Colour) + get_framebuffer_width() * sizeof(uwe::Colour) * y;
             context_.set_pixel(offset, colour);
        }

        void clear_framebuffer(Colour colour) {
            for (int offset = 0; offset < get_framebuffer_width() * get_framebuffer_height() * 4; offset++) {
                context_.set_pixel(offset, colour);
            }
        }

        void blit_framebuffer() {
            // copy framebuffer pixels to GPU texture for rendering
            SDL_UpdateTexture(
                context_.get_texture(),
                NULL,
                context_.get_pixels().data(),
                context_.get_tex_width() * 4);

            SDL_RenderCopy( context_.get_renderer(), context_.get_texture(), NULL, NULL );
        }

        void clear(Colour colour) {
            SDL_SetRenderDrawColor( 
                context_.get_renderer(), 
                colour.red_,
                colour.green_,
                colour.blue_,
                colour.alpha_ );
            SDL_RenderClear( context_.get_renderer() );
        }

        Font create_font(std::string path, int point_size, Colour colour) {
            return context_.create_font(path, point_size, colour);
        }

        void draw_font(Font font, std::string msg, float x, float y) {
            context_.draw_font(font, msg, x, y);
        }

        Image create_image(std::string path) {
            return context_.create_image(path);
        }

        Image create_image(int image_width, int image_height) {
            return context_.create_image(image_width, image_height);
        }

        void get_image_size(Image image, int *width, int *height) {
            context_.get_image_size(image, width, height);
        }

        void draw_image(Image image, Rect src, Rect dest) {
            context_.draw_image(image, src, dest);
        }

        void set_renderer_taret(Image image, bool clear) {
            SDL_SetRenderTarget(context_.get_renderer(), image);
            if (clear) {
                SDL_RenderClear(context_.get_renderer());
            }
        }

        // drawing
        void set_draw_color(Colour colour) {
            SDL_SetRenderDrawColor( 
                context_.get_renderer(), 
                colour.red_,
                colour.green_,
                colour.blue_,
                colour.alpha_ );
        }

        void draw_rect(int x, int y, int width, int height) {
            Rect rect = make_rect(x, y, width, height);
            SDL_RenderDrawRect(context_.get_renderer(), &rect);
        }

        void draw_rect(Rect rect) {
            SDL_RenderDrawRect(context_.get_renderer(), &rect);
        }

        void draw_rect_fill(int x, int y, int width, int height) {
            Rect rect = make_rect(x, y, width, height);
            SDL_RenderFillRect(context_.get_renderer(), &rect);
        }

        void draw_rect_fill(Rect rect) {
            SDL_RenderFillRect(context_.get_renderer(), &rect);
        }

        void draw_line(int x1, int y1, int x2, int y2) {
            SDL_RenderDrawLine(context_.get_renderer(), x1, y1, x2, y2);
        }

        void draw_point(int x, int y) {
            SDL_RenderDrawPoint(context_.get_renderer(), x, y);
        }
    };

    void run();
} // namespace uwe