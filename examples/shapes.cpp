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
    uwe::Image text_;
    int text_width_;
    int text_height_;

    uwe::Image some_text_;

    uwe::Font font15_;
public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    void begin() override;
    void update() override;
    void draw() override;

    void key_pressed(uwe::Scancode scancode, bool repeat) override;

    uwe::Image render_text(std::string msg);
};

MyApp::MyApp(int width, int height, std::string title): 
    width_{width},
    height_{height} {
        init(width, height, title);
}

MyApp::~MyApp() {

}

void MyApp::begin() {
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    text_ = create_image("./assets/ZX_Spectrum_character_set.png");
#else
    text_ = create_image("../assets/ZX_Spectrum_character_set.png");
#endif
    get_image_size(text_, &text_width_, &text_height_);

    some_text_ = render_text("abc");

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    font15_ = create_font("./assets/fonts/FreeSans.ttf", 15, uwe::Colour::red());
#else
    font15_ = create_font("../assets/fonts/FreeSans.ttf", 15, uwe::Colour::red());
#endif

}

void MyApp::update() {

}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat) {
    if( scancode == uwe::Scancode::L) {
        toggle_framerate();
    }
}

void MyApp::draw() {
    clear(uwe::Colour::white());

    set_draw_color(uwe::Colour::red());
    draw_rect(20,20,100,100);

    set_draw_color(uwe::Colour::blue());
    draw_rect_fill(100,100,100,100);

    draw_line(300, 300, 350, 400);

    set_draw_color(uwe::Colour::green());
    draw_point(400, 100);

    draw_image(text_, uwe::make_rect(0,0,text_width_,text_height_), uwe::make_rect(200,200,text_width_,text_height_));

    draw_font(font15_, "This is a msg", 300, 100);


    int width;
    int height;
    get_image_size(some_text_, &width, &height);
    draw_image(some_text_, uwe::make_rect(0,0, width, height), uwe::make_rect(150,30, width, height) );
}

uwe::Image MyApp::render_text(std::string msg) {
    int max_width = 0;
	int num_lines = 1;
	int current_width = 0;

	for (auto const c : msg) {
		if (c != '\n')
			current_width++;
		else {
			num_lines++;
			if (current_width > max_width)
				max_width = current_width;
			current_width = 0;
		}
	}
	if (current_width > max_width) {
		max_width = current_width;
    }
	int text_width = max_width * 16;
	int text_height = num_lines * 16;

    auto image = create_image(text_width, text_height);

    set_draw_color(uwe::Colour::white());
    set_renderer_taret(image, true);

    int x = 0; int y = 0;
	for (auto const c : msg) {
		if (c != '\n') {
			// Figure out what character it is
			int code = c - 32;
			if (c == '$') {
				code = 64;
            }
			uwe::Rect src{ (code % 16)*16, (code / 16)*16, 16, 16 };
			uwe::Rect dest{ x, y, 16, 16 };
			draw_image(text_, src, dest);
			x += 16;
		} else {
			x = 0;
			y+=16;
		}
	}

    set_renderer_taret(nullptr, true);

    return image;
}

int main(int argc, char *argv[]) {
    
    uwe::App* app = new MyApp{width, height, "Shapes Example"};

    app->run();

    return 0;
}