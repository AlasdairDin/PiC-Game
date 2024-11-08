#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <tuple>

#include <context.hpp>
#include <app.hpp>

using namespace std;

const int width = 640;
const int height = 480;

const int COLOUR_INDEX_X = 30;
const int COLOUR_INDEX_Y = 420;

const int COLOUR_PALATE_WIDTH = 20;
const int COLOUR_PALATE_HEIGHT = 20;

const int COLOUR_CURRENT_X = 30;
const int COLOUR_CURRENT_Y = 30;

const int SPRITE_WIDTH = 16;
const int SPRITE_HEIGHT = 16;

const int SPRITE_DISPLAY_X = 500;
const int SPRITE_DISPLAY_Y = 220;

const int SPRITE_EDITOR_X = 250;
const int SPRITE_EDITOR_Y = 150;

const int SPRITE_EDITOR_PIXELS_WIDTH = 8;
const int SPRITE_EDITOR_PIXELS_HEIGHT = 8;

const int SPRITE_EDITOR_CELL_TIMES = 8;

const int SPRITE_START_X = 100;
const int SPRITE_START_Y = 100;

class MyApp: public uwe::App {
private:
    int width_;
    int height_;
    
    int colour_index_x_;
    int colour_index_y_;
    int colour_index_overall_width_;
    vector<uwe::Colour> colour_palate_;

    uwe::Colour current_colour_;

    vector<uwe::Colour> sprite_;

    int sprite_x_;
    int sprite_y_;

    bool mouse_down_;

    bool editor_active_;
public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    size_t number_colours() const {
        return colour_palate_.size();
    }

    bool hit_palate(int x, int y, size_t& hit_index) {
        if (x >= colour_index_x_ && x <= colour_index_overall_width_ * number_colours() &&
            y >= colour_index_y_ && y <= colour_index_y_ + COLOUR_PALATE_HEIGHT) {
                hit_index = (x - colour_index_x_) / COLOUR_PALATE_WIDTH;
                return true;
        }

        return false;
    }

    bool hit_editor(int x, int y, size_t& hit_index) {
        if (x >= SPRITE_EDITOR_X && x <= SPRITE_EDITOR_X + SPRITE_EDITOR_PIXELS_WIDTH*SPRITE_WIDTH &&
            y >= SPRITE_EDITOR_Y && y <= SPRITE_EDITOR_Y + SPRITE_EDITOR_PIXELS_HEIGHT*SPRITE_HEIGHT ) {
                hit_index = (x - SPRITE_EDITOR_X) / (SPRITE_EDITOR_PIXELS_WIDTH);
                int tmp = (y - SPRITE_EDITOR_Y) / SPRITE_EDITOR_PIXELS_HEIGHT;
                hit_index = hit_index + SPRITE_WIDTH*tmp;
                return true;
        }
        return false;
    }

    void begin() override;
    void update() override;
    void draw() override;

    void key_pressed(uwe::Scancode scancode, bool repeat) override;

    void mouse_pressed(int x, int y, uwe::Button button) override;
    void mouse_released(int x, int y, uwe::Button button) override;
    void mouse_moved(int x, int y) override;
};

MyApp::MyApp(int width, int height, std::string title): 
    width_{width},
    height_{height},
    colour_index_x_{COLOUR_INDEX_X},
    colour_index_y_{COLOUR_INDEX_Y},
    current_colour_{uwe::Colour::black()},
    sprite_(SPRITE_WIDTH*SPRITE_HEIGHT, uwe::Colour::white()),
    mouse_down_{false},
    editor_active_{false},
    sprite_x_{SPRITE_START_X},
    sprite_y_{SPRITE_START_Y} {
        init(width, height, title);

        colour_palate_.push_back(uwe::Colour::white());
        colour_palate_.push_back(uwe::Colour::green());
        colour_palate_.push_back(uwe::Colour::blue());
        colour_palate_.push_back(uwe::Colour::red());

        colour_index_overall_width_ = COLOUR_PALATE_WIDTH * number_colours();

        current_colour_ = colour_palate_[0];
}

MyApp::~MyApp() {

}

void MyApp::begin() {
    
}

void MyApp::update() {

}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat) {
    switch (scancode) {
        // enable framerate dump
        case uwe::Scancode::L: {
            toggle_framerate();
            break;
        }
        // switch to editor
        case uwe::Scancode::D_1: {
            editor_active_ = false;
            break;
        }
        // switch to scene
        case uwe::Scancode::D_2: {
            editor_active_ = true;
            break;
        }
        case uwe::Scancode::LEFT: {
            if (!editor_active_) {
                sprite_x_ = sprite_x_ - 2;
            }
            break;
            // TODO: bounds check against window
        }
        case uwe::Scancode::RIGHT: {
            if (!editor_active_) {
                sprite_x_ = sprite_x_ + 2;
            }
            break;
        }
        case uwe::Scancode::UP: {
            if (!editor_active_) {
                sprite_y_ = sprite_y_ - 4;
            }
            break;
        }
        case uwe::Scancode::DOWN: {
            if (!editor_active_) {
                sprite_y_ = sprite_y_ + 2;
            }
            break;
        }
        default: {
            // nothing see here
        }
    }
}

void MyApp::mouse_pressed(int x, int y, uwe::Button button) {
    if (editor_active_) {
        size_t hit_index;
        if (hit_palate(x, y, hit_index)) {
            current_colour_ = colour_palate_[hit_index];
        }
        else if (hit_editor(x, y, hit_index)) {
            sprite_[hit_index] = current_colour_;
        }
    }

    mouse_down_ = true;
}
    
void MyApp::mouse_released(int x, int y, uwe::Button button) {
    mouse_down_ = false;
}
    
void MyApp::mouse_moved(int x, int y) {
    size_t hit_index;
    if (mouse_down_ && hit_editor(x, y, hit_index)) {
        sprite_[hit_index] = current_colour_;
    }
}

void MyApp::draw() {
    clear(uwe::Colour::black());

    // Below we demostrate the use of both the framebuffer and drawing primitives.
    clear_framebuffer(uwe::Colour::black());

    if (editor_active_) {
        // draw sprite as actually seen
        int i = 0;
            for (int y = 0; y < SPRITE_HEIGHT; y++) {
                for (int x = 0; x < SPRITE_WIDTH; x++) {
                // draw sprite as actually seen
                set_framebuffer(x + SPRITE_DISPLAY_X, y + SPRITE_DISPLAY_Y, sprite_[i]);

                // draw sprite editor
                for (int y_times = 0; y_times < SPRITE_EDITOR_PIXELS_HEIGHT; y_times++) {
                    for (int x_times = 0; x_times < SPRITE_EDITOR_PIXELS_WIDTH; x_times++) {
                        set_framebuffer(
                            x*SPRITE_EDITOR_PIXELS_WIDTH + SPRITE_EDITOR_X + x_times, 
                            y*SPRITE_EDITOR_PIXELS_HEIGHT + SPRITE_EDITOR_Y + y_times, 
                            sprite_[i]);
                    }
                }
                i++;
            }
        }

        blit_framebuffer();

        // draw colour palate
        for (int i = 0; i < number_colours(); i++) {
            set_draw_color(colour_palate_[i]);
            draw_rect_fill(
                colour_index_x_ + i*COLOUR_PALATE_WIDTH, colour_index_y_, COLOUR_PALATE_WIDTH, COLOUR_PALATE_HEIGHT);
        }

        // draw current colour
        set_draw_color(current_colour_);
        draw_rect_fill(COLOUR_CURRENT_X, COLOUR_CURRENT_Y, COLOUR_PALATE_WIDTH, COLOUR_PALATE_HEIGHT);
    }
    else {
        // draw scene
        int i = 0;
        for (int y = 0; y < SPRITE_HEIGHT; y++) {
            for (int x = 0; x < SPRITE_WIDTH; x++) {
                // draw sprite as actually seen
                set_framebuffer(x + sprite_x_, y + sprite_y_, sprite_[i]);
                i++;
            }
        }
        blit_framebuffer();
    }
}

int main(int argc, char *argv[]) {
    uwe::App* app = new MyApp{width, height, "Sprite Example"};

    app->run();

    return 0;
}