#include <iostream>

#include <context.hpp>
#include <iomanip>
#include <cstring>

namespace uwe {
    Context::Context() {
    } 

    void Context::init(int width, int height, std::string title) {
        width_ =  width; 
        height_ = height;
        tex_width_ = width;
        tex_height_ = height;
        pixels_ = std::vector<uint8_t>(tex_width_ * tex_height_ *4),
        SDL_Init( SDL_INIT_EVERYTHING );

        window_ = SDL_CreateWindow(
            "SDL2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width_, height_,
            SDL_WINDOW_SHOWN);

        SDL_SetWindowTitle(window_, title.c_str());

        renderer_ = SDL_CreateRenderer(
            window_,
            -1,
            SDL_RENDERER_ACCELERATED);

        texture_ = SDL_CreateTexture(
            renderer_,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            tex_width_, 
            tex_height_);
    }

    Context::~Context() {
        for (auto font: loaded_fonts_) {
            FC_FreeFont(font);
        }

        SDL_DestroyRenderer( renderer_ );
        SDL_DestroyWindow( window_ );
        SDL_Quit();
    }

    // void Context::run() {
    

    void Context::dump_renderer_info() {
        SDL_RendererInfo info;
        SDL_GetRendererInfo( renderer_, &info );
        std::cout << "Renderer name: " << info.name << std::endl;
        std::cout << "Texture formats: " << std::endl;
        for( uint32_t i = 0; i < info.num_texture_formats; i++ ) {
            std::cout << SDL_GetPixelFormatName( info.texture_formats[i] ) << std::endl;
        }
    }
}