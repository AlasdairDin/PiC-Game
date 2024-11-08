#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <tuple>
#include <windows.h>
#include <context.hpp>
#include <app.hpp>

using namespace std;

const int width = 640;
const int height = 480;
class MyApp : public uwe::App
{
private:
    int cntDebug = 0;
    
    uwe::Font font15_;
    // Starting grid rendering varibles to make it Dynamic
    int tilex = (width - 300) / 3;
    int tiley = (height - 200) / 3;
    int offsetx = tilex / 10;
    int offsety = tiley / 10;

    uwe::Image cross_;
    uwe::Image nought_;
    // Game Operation Varibles
    enum TILE_STATE //define the different states that the tiles can be
    {
        EMPTY,
        NOUGHT,
        CROSS
    };
    TILE_STATE scores[3][3] = {{EMPTY}};    //Grid to show what state each tile is
    TILE_STATE active_player = NOUGHT;      //the current player starting on Nought
    TILE_STATE winner = EMPTY;              //The round Winner
    bool tie = false;                       //checks for tie condition
    bool playerSwitchLatch = false;         //Makes sure the player only changes if they have clicked on a empty tile

    //Previous Score Grid
    TILE_STATE previous[3][3] = {{EMPTY}};  //the previous result

    //Scores of each player and teh varible used to display them
    int nought_score = 0;
    int cross_score = 0;
    string nght_score = "0";
    string crs_score = "0";
    bool winCounterLatch = false;           //Makes sure that the score only increases if you have one a match (fixes spam clicking after win bug)

    int cntWinner = 0; //End of round delay varible
    int winState = 10;
public:
    MyApp(int width, int height, std::string title);
    ~MyApp();

    void begin() override;
    void update() override;
    void draw() override;

    void key_pressed(uwe::Scancode scancode, bool repeat) override;

    void mouse_pressed(int x, int y, uwe::Button button) override;
    void mouse_released(int x, int y, uwe::Button button) override;
    void mouse_moved(int x, int y) override;

    uwe::Image render_text(std::string msg);
};

MyApp::MyApp(int width, int height, std::string title)
{
    init(width, height, title);
}

MyApp::~MyApp()
{
}

void MyApp::begin()
{
//Image Loading
    //Cross.png Loading
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    cross_ = create_image("./assets/Cross.png");
#else
    cross_ = create_image("../assets/Cross.png");
#endif
    //nought.png Loading
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    nought_ = create_image("./assets/Nought.png");
#else
    nought_ = create_image("../assets/Nought.png");
#endif

// Font Loading
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
    font15_ = create_font("./assets/fonts/PlasticLoveRegular.ttf", 30, uwe::Colour::black());
#else
    font15_ = create_font("../assets/fonts/PlasticLoveRegular.ttf", 30, uwe::Colour::black());
#endif
}

void MyApp::update()
{
    //DEBUGGING (COMMENT OUT IF NOT WANTED)
    if (cntDebug++ > 1000)
    {
        system("cls");
        cout << endl;
        cout << scores[0][0] << " | " << scores[1][0] << " | " << scores[2][0] << endl;
        cout << "--+---+--" << endl;
        cout << scores[0][1] << " | " << scores[1][1] << " | " << scores[2][1] << endl;
        cout << "--+---+--" << endl;
        cout << scores[0][2] << " | " << scores[1][2] << " | " << scores[2][2] << endl;
        cout << endl;
        cout << "Winner: " << winner << endl;
        cout << "Draw: "<< tie << endl;
        cout << "Score Counter Latch: "<< winCounterLatch << endl;
        cout << "Player Switch Latch: "<< playerSwitchLatch << endl;
        cout << "Win State: "<< winState << endl;
        cout << endl;
        cntDebug = 0;
    }

    //convert scores to strings for font rendering
    nght_score = to_string(nought_score);
    crs_score = to_string(cross_score);

    if ((winner != EMPTY) || (tie == true)) //adding end of round delay
    {
        if (cntWinner++ > 10000) //win message delay
        {
            winner = EMPTY; //wipes end round status
            tie = false;    // ^^
            cntWinner = 0;
            winState = 10;
            for (int x = 0; x < 3; ++x)
            {
                for (int y = 0; y < 3; ++y)
                {
                    scores[x][y] = EMPTY; //Clears board
                }
            }
        }
    }



}

void MyApp::key_pressed(uwe::Scancode scancode, bool repeat)
{
    switch (scancode)
    {
    default:
    {
        // nothing to see here
    }
    }
}

void MyApp::mouse_pressed(int x, int y, uwe::Button button)
{
}

void MyApp::mouse_released(int x, int y, uwe::Button button)
{
    //Hit Detection
    if (winner == EMPTY) {
        for (int j = 0; j < 3; ++j)
        { // J = X-axis   I = Y-axis
            for (int i = 0; i < 3; ++i)
            {
                if ((x >= ((j * tilex) + (j * offsetx))) && (y >= ((i * tiley) + (i * offsety))) && (y <= ((i * tiley) + (i * offsety) + tiley)) && (x <= ((j * tilex) + (j * offsetx) + tilex)) && scores[j][i] == EMPTY)
                {
                    scores[j][i] = active_player;   //Sets tile to the active player
                    playerSwitchLatch = true;       //Makes sure that the player only switches when a tile is changed
                }
            }
        }
    }

    //win detection
    // Check for horizontal lines.
    for (int i = 0; i < 3; i++)
    {
        if (((scores[0][i] == scores[1][i] && scores[1][i] == scores[2][i]) && scores[0][i] != EMPTY) && (winner == EMPTY))
        {
            winner = active_player;
            winCounterLatch = true;
            winState = i;
        }
    }
    // Check for vertical lines.
    for (int i = 0; i < 3; i++)
    {
        if (((scores[i][0] == scores[i][1] && scores[i][1] == scores[i][2]) && scores[i][0] != EMPTY) && (winner == EMPTY))
        {
            winner = active_player;
            winCounterLatch = true;
            winState = i + 3;
        }
    }
    // Check for top-left to bottom-right diagonals.
    if (((scores[0][0] == scores[1][1] && scores[1][1] == scores[2][2]) && scores[0][0] != EMPTY) && (winner == EMPTY))
    {
        winner = active_player;
        winCounterLatch = true;
        winState = 6;
    }
    // Check for top-rght to bottom-left diagonals.
    if (((scores[2][0] == scores[1][1] && scores[1][1] == scores[0][2]) && scores[2][0] != EMPTY) && (winner == EMPTY))
    {
        winner = active_player;
        winCounterLatch = true;
        winState = 7;
    }
    //Draw Detection
    if ((scores[0][0] != EMPTY) && (scores[0][1] != EMPTY) && (scores[0][2] != EMPTY) &&
        (scores[1][0] != EMPTY) && (scores[1][1] != EMPTY) && (scores[1][2] != EMPTY) &&
        (scores[2][0] != EMPTY) && (scores[2][1] != EMPTY) && (scores[2][2] != EMPTY) && (winner == EMPTY))
    {
        tie = true;
    }

    //Player Switch
    if ((active_player == NOUGHT) && (playerSwitchLatch == true))
    {
        active_player = CROSS; //switches player
        playerSwitchLatch = false; //ensures that player cant switch without playing a turn
    }
    else if ((active_player == CROSS) && (playerSwitchLatch == true))
    {
        active_player = NOUGHT;
        playerSwitchLatch = false;
    }

    //Score Calculator
    if ((winner == NOUGHT) && (winCounterLatch == true))
    {
        ++nought_score;
        winCounterLatch = false;
    }
    else if ((winner == CROSS) && (winCounterLatch == true))
    {
        ++cross_score;
        winCounterLatch = false;
    }

    //Save Previous Game
    if ((winner != EMPTY) || (tie == true)) //Check for round end
    {
        for (int j = 0; j < 3; ++j)
        { 
            for (int i = 0; i < 3; ++i)
            {
                previous[i][j] = scores[i][j]; //save previous round to 2nd array

            }
        }
    }
}

void MyApp::mouse_moved(int x, int y)
{
}

void MyApp::draw()
{
    // Draw Starting Board
    clear(uwe::Colour::white());
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            set_draw_color(uwe::Colour::Colour(226, 229, 222,255));
            draw_rect_fill(((x * tilex) + (x * offsetx) + offsetx), ((y * tiley) + (y * offsety) + offsety), tilex, tiley);
        }
    }
    draw_font(font15_, "TIC TAC TOE", width - 230, 40);

    //Update board after clicks
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (scores[x][y] == NOUGHT) //Draws Nought onto board
            {
                set_draw_color(uwe::Colour::blue());
                draw_rect_fill(((x * tilex) + (x * offsetx) + offsetx), ((y * tiley) + (y * offsety) + offsety), tilex, tiley);
                draw_image(nought_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect(((x * tilex) + (x * offsetx) + offsetx), ((y * tiley) + (y * offsety) + offsety), tilex, tiley));
            }
            else if (scores[x][y] == CROSS) //Draws Cross onto Board
            {
                set_draw_color(uwe::Colour::red());
                draw_rect_fill(((x * tilex) + (x * offsetx) + offsetx), ((y * tiley) + (y * offsety) + offsety), tilex, tiley);
                draw_image(cross_, uwe::make_rect(0, 0, 296, 253), uwe::make_rect(((x * tilex) + (x * offsetx) + offsetx), ((y * tiley) + (y * offsety) + offsety), tilex, tiley));
            }
            else if (scores[x][y] == EMPTY) //Emptys tiles at round restart
            {
                set_draw_color(uwe::Colour::Colour(128, 128, 128,255));
                draw_rect_fill(((x * tilex) + (x * offsetx) + offsetx), ((y * tiley) + (y * offsety) + offsety), tilex, tiley);
            }
        }
    }

    //Win Highlighter
    set_draw_color(uwe::Colour::green());
        //Highlight Horiozontal Wins
    if ((winState >= 0) && (winState <= 2)) {
        for (int i = 0; i < 3; ++i) {
            draw_rect_fill(((i * tilex) + (i * offsetx) + offsetx),  ((winState * tiley) + (winState * offsety) + offsety), tilex, tiley);
            if (winner == NOUGHT) {
                draw_image(nought_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect(((i * tilex) + (i * offsetx) + offsetx),  ((winState * tiley) + (winState * offsety) + offsety), tilex, tiley));
            }
            if (winner == CROSS) {
                draw_image(cross_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect(((i * tilex) + (i * offsetx) + offsetx),  ((winState * tiley) + (winState * offsety) + offsety), tilex, tiley));
            }
        }
    }
        //HighLight Vertical Wins
    if ((winState >= 3) && (winState <= 5)) {
        for (int i = 0; i < 3; ++i) {
            draw_rect_fill((((winState -3 ) * tilex) + ((winState - 3) * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley);
            if (winner == NOUGHT) {
                draw_image(nought_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect((((winState -3 ) * tilex) + ((winState - 3) * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley));
            }
            if (winner == CROSS) {
                draw_image(cross_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect((((winState -3 ) * tilex) + ((winState - 3) * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley));
            }
        }
    }
        //Highlight top-left to bottom-right diagonal wins
    if (winState == 6) {
        for (int i = 0; i < 3; ++i) {
            draw_rect_fill(((i * tilex) + (i * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley);
            if (winner == NOUGHT) {
                draw_image(nought_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect(((i * tilex) + (i * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley));
            }
            if (winner == CROSS) {
                draw_image(cross_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect(((i * tilex) + (i * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley));
            }
        }
    }
        //Highlight top-right to bottom-left diagonal wins
    if (winState == 7) {
        for (int i = 0; i < 3; ++i) {
            draw_rect_fill((((2 - i) * tilex) + ((2 - i) * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley);
            if (winner == NOUGHT) {
                draw_image(nought_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect((((2 - i) * tilex) + ((2 - i) * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley));
            }
            if (winner == CROSS) {
                draw_image(cross_, uwe::make_rect(0, 0, 300, 238), uwe::make_rect((((2 - i) * tilex) + ((2 - i) * offsetx) + offsetx),  ((i * tiley) + (i * offsety) + offsety), tilex, tiley));
            }
        }
    }
    //Winning Messages
    set_draw_color(uwe::Colour::black());
    if (winner == NOUGHT)
    {
        draw_font(font15_, "NOUGHTS WIN!", width - 250, 100);
    }
    else if (winner == CROSS)
    {
        draw_font(font15_, "CROSSES WIN!", width - 250, 100);
    }
    else if (tie == true)
    {
        draw_font(font15_, "DRAW!", width - 250, 100);
    }

    //Scoreboard
    draw_font(font15_, "NOUGHTS: " + nght_score, 40, height - 120);
    draw_font(font15_, "CROSSES: " + crs_score, 40, height - 75);

    //previous winner grid
    draw_font(font15_, "PREVIOUS GAME", width - 250, height - 230);
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (previous[x][y] == NOUGHT) //Draws Nought onto board
            {
                set_draw_color(uwe::Colour::blue());
                draw_rect_fill(((x * 50) + (x * 5) + (width - 210)), ((y * 50) + (y * 5) + (height - 200)), 50, 50);
                draw_image(nought_, uwe::make_rect(0, 0, 296, 253), uwe::make_rect(((x * 50) + (x * 5) + (width - 210)), ((y * 50) + (y * 5) + (height - 200)), 50, 50));
            }
            else if (previous[x][y] == CROSS) //Draws Cross onto Board
            {
                set_draw_color(uwe::Colour::red());
                draw_rect_fill(((x * 50) + (x * 5) + (width - 210)), ((y * 50) + (y * 5) + (height - 200)), 50, 50);
                draw_image(cross_, uwe::make_rect(0, 0, 296, 253), uwe::make_rect(((x * 50) + (x * 5) + (width - 210)), ((y * 50) + (y * 5) + (height - 200)), 50, 50));
            }
            else if (previous[x][y] == EMPTY) //Draws Empty Tiles
            {
                set_draw_color(uwe::Colour::Colour(103, 103, 103, 255));
                draw_rect_fill(((x * 50) + (x * 5) + (width - 210)), ((y * 50) + (y * 5) + (height - 200)), 50, 50);
            }
        }
    }

}

int main(int argc, char *argv[])
{
    uwe::App *app = new MyApp{width, height, "Assignment"};

    app->run();

    return 0;
}