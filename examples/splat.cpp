#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

#include <context.hpp>
#include <app.hpp>

const int width = 640;
const int height = 480;

class MyApp: public uwe::App {
private:
    int width_;
    int height_;
public:
    MyApp(int width, int height, std::string);
    ~MyApp();

    void begin() override;
    void update() override;
    void draw() override;

    void key_pressed(uwe::Scancode scancode, bool repeat) override;
};

MyApp::MyApp(int width, int height, std::string title): 
    width_{width},
    height_{height} {
        init(width, height, title);
}

MyApp::~MyApp() {

}

void MyApp::begin() {

}

void MyApp::update() {

}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat) {
    if( scancode == uwe::Scancode::L) {
        toggle_framerate();
    }
}

void MyApp::draw() {
    clear(uwe::Colour::black());

    for( unsigned int i = 0; i < 1000; i++ ) {
        const unsigned int x = rand() % get_framebuffer_width();
        const unsigned int y = rand() % get_framebuffer_height();

        const unsigned int offset = ( get_framebuffer_width() * 4 * y ) + x * 4;

        set_framebuffer_non_scaled(
            offset, 
            uwe::Colour{
                static_cast<uint8_t>(rand() % 256), 
                static_cast<uint8_t>(rand() % 256), 
                static_cast<uint8_t>(rand() % 256), 
                SDL_ALPHA_OPAQUE});
    }

    blit_framebuffer();
}


int main( int argc, char** argv ) {
    uwe::App* app = new MyApp{width, height, "Splat Example"};

    //app->dump_renderer_info();
    app->run();

    return 0;
}