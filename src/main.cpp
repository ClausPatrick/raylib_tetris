#include <iostream>
#include <memory>
#include <ostream>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <string>
#include <vector>

#include "c_logger.h"
#include "colours.h"
#include "game.h"

char log_buffer[1024];


const char screenshot_path[] = "screenshots/take_6/";

#define RAYLIB_ENABLED 1
#define SCREEN_W 500
#define SCREEN_H 620
#define GRID_CELL_SIZE 12
#define ENABLE_SCREEN_CAPTURE 0
#define SCREEN_CAPTURE_MAX_COUNT 1000 
#define LD_RATIO 0.2
#define RANDOM_SEED 1


static Color dark_green_bg = {44, 127, 44, 255};

double last_time = 0;

void capture_screen(){
    static size_t capture_count = 0;
    if (capture_count < SCREEN_CAPTURE_MAX_COUNT){
        char file_name[255];
        sprintf(file_name, "%sscreen_%ld.png", screenshot_path, capture_count);
        TakeScreenshot(file_name);
        sprintf(log_buffer, "%s: '%s'.", __func__, file_name);
        capture_count++;
        logger(log_buffer, 4);
    }
}

bool is_event_triggered(double interval){
    double current_time = GetTime();
    if (current_time - last_time >= interval){
        last_time = current_time;
        return true;
    }
    return false;
}


int main(){

#if RAYLIB_ENABLED
    InitWindow(SCREEN_W, SCREEN_H, "Tetris");
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Game game = Game();
    SetTargetFPS(60);
    //ToggleBorderlessWindowed();
    while (WindowShouldClose() == false){
        game.handle_input();
        UpdateMusicStream(game.musics[game.music_selector]);
        if (is_event_triggered(game.get_difficulty_factor()) && game.is_running()){
            game.move_block_down();
        }
        BeginDrawing();
        ClearBackground(dark_green_bg);
//        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
//        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
//        if (game.is_over()){
//            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, RED);
//        }
//        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, dark_blue);
//
//        char score_text[12];
//        sprintf(score_text, "%d", game.score);
//        Vector2 text_size = MeasureTextEx(font, score_text, 38, 2);
//        DrawTextEx(font, score_text, {320 + (170 - text_size.x) / 2, 65}, 38, 2, WHITE);
//        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, dark_blue);
        game.draw();
        EndDrawing();
        if (ENABLE_SCREEN_CAPTURE){
            //if (world.get_state() == _RUN){
                capture_screen();
            //}
        }
    }
    CloseWindow();
#endif //RL ENABLED
    sprintf(log_buffer, "Main is done.");
    logger(log_buffer, 4);
    return 0;
}
