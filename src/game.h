#pragma once
#include "grid.h"
#include "options.h"
#include "scoring.h"
#include "blocks.h"





class Game {
public:
    Game();
    ~Game();
    Options options;
    Option_Parameters* option_parameters;
    void draw();
    void handle_options();
    void handle_input();
    void play_sound(Sound sound);
    void play_music(uint8_t theme);
    void stop_music(uint8_t theme);
    void pause_music(uint8_t theme);
    void resume_music(uint8_t theme);
    bool paused;
    void move_block_down();
    bool game_over;
    void over();  // game over
    int score;
    uint8_t music_selector;
    Music music_a;
    Music music_b;
    Music music_c;
    Music musics[3];
    bool is_running();
    bool is_over();
    bool is_paused();
    double get_difficulty_factor();
    //Options options = Options();

private:
    Font font;
    void move_block_left();
    void move_block_right();
    Block get_random_block();
    std::vector<Block> get_all_blocks();
    bool is_block_outside();
    void rotate_block_r();
    void rotate_block_l();
    void lock_block();
    bool block_fits();
    void reset();
    void update_score(int lines_cleared, int move_down_points);
    Grid grid;
    std::vector<Block> blocks;
    Block current_block;
    Block next_block;
    Sound game_over_sound;
    Sound rotate_sound;
    Sound clear1_sound;
    Sound clear2_sound;
    Sound clear3_sound;
    Sound clear4_sound;
    Sound clear_sounds[4];
    Sound pause_sound;
    Sound unpause_sound;
    bool m_sound_muted;
    uint8_t m_state;
    uint8_t m_difficulty_level;
    double m_difficulty_factor[4];
    char m_top_score_text[3][24];
    bool m_top_score_calculated;
    uint8_t m_top_score_counter;
};
