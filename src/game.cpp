#include "game.h"
#include <random>

enum game_state{
    state_run,
    state_pause,
    state_over
};
    

Game::Game() {
    grid = Grid();
    //options = Options();   // Not needed, will call constructor twice!
    blocks = get_all_blocks();
    current_block = get_random_block();
    next_block = get_random_block();
    game_over = false;
    paused = false;
    m_state = state_run;
    score = 0;
    InitAudioDevice();
    music_a = LoadMusicStream("sounds/tetris_a.mp3");
    music_b = LoadMusicStream("sounds/tetris_b.mp3");
    music_c = LoadMusicStream("sounds/tetris_c.mp3");
    music_selector = 0;
    m_sound_muted = false;
    m_difficulty_level = 0;
    musics[0] = music_a;
    musics[1] = music_b;
    musics[2] = music_c;
    game_over_sound = LoadSound("sounds/game_over.mp3");
    rotate_sound = LoadSound("sounds/rotate.mp3");
    clear1_sound = LoadSound("sounds/clear1.mp3");
    clear2_sound = LoadSound("sounds/clear2.mp3");
    clear3_sound = LoadSound("sounds/clear3.mp3");
    clear4_sound = LoadSound("sounds/clear4.mp3");
    pause_sound = LoadSound("sounds/pause.mp3");
    unpause_sound = LoadSound("sounds/unpause.mp3");
    clear_sounds[0] = clear1_sound;
    clear_sounds[1] = clear2_sound;
    clear_sounds[2] = clear3_sound;
    clear_sounds[3] = clear4_sound;
    play_music(music_selector);
    m_state = 0;
    m_difficulty_factor[0] = 0.5;
    m_difficulty_factor[1] = 0.2;
    m_difficulty_factor[2] = 0.1;
    m_difficulty_factor[3] = 0.5;
    m_top_score_calculated = false;
    m_top_score_counter = 0;
    font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    //option_parameters.theme_nr = 0;
    //option_parameters.sound_enabled = true;
    //option_parameters.difficulty_level = 0;
}

Game::~Game() {
    UnloadSound(rotate_sound);
    UnloadSound(clear1_sound);
    UnloadSound(clear2_sound);
    UnloadSound(clear3_sound);
    UnloadSound(clear4_sound);
    UnloadSound(pause_sound);
    UnloadSound(unpause_sound);
    UnloadMusicStream(music_a);
    UnloadMusicStream(music_b);
    UnloadMusicStream(music_c);
    CloseAudioDevice();
}

Block Game::get_random_block() {
    if (blocks.empty()) {
        blocks = get_all_blocks();
    }
    int random_index = rand() % blocks.size();
    Block block = blocks[random_index];
    blocks.erase(blocks.begin() + random_index);
    return block;
}

std::vector<Block> Game::get_all_blocks() {
    return {i_Block(), j_Block(), l_Block(), o_Block(), s_Block(), t_Block(), z_Block()};
}

void Game::draw() {
        DrawTextEx(font, "Score", {365, 15}, 28, 2, light_green);
        DrawTextEx(font, "Next", {370, 175}, 28, 2, light_green);
       // if (game.is_over()){
        if (is_over()){
            DrawTextEx(font, "GAME OVER", {300, 550}, 30, 2, RED);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, dark_blue);

        char score_text[64];
        sprintf(score_text, "%d", score);
        Vector2 text_size = MeasureTextEx(font, score_text, 38, 2);
        DrawTextEx(font, score_text, {320 + (170 - text_size.x) / 2, 65}, 38, 2, light_green);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, dark_blue);
        

        
        if (m_top_score_calculated == false){
            m_top_score_calculated = true;

            size_t top_score;
            char top_name[4];
            char top_date[16];
            m_top_score_counter = 0;

            for (size_t i=0; i<3; i++){

                int r = options.get_ranking(i, &top_score, top_name, top_date);
                if (r==0){
                    m_top_score_counter++;
                    char tdy[3];
                    char tdm[3];
                    char tdd[3];
                    tdy[0] = top_date[0];
                    tdy[1] = top_date[1];
                    tdy[2] = '\0';
                    tdm[0] = top_date[2];
                    tdm[1] = top_date[3];
                    tdm[2] = '\0';
                    tdd[0] = top_date[4];
                    tdd[1] = top_date[5];
                    tdd[2] = '\0';

                    sprintf(m_top_score_text[i], "%s, %ld, %s-%s-%s", top_name, top_score, tdy, tdm, tdd);
                }
            }
        }
        
        
        if (m_top_score_counter > 0){
            DrawTextEx(font, "Top scores:", {326, 410}, 16, 2, light_green);
            for (size_t i=0; i<m_top_score_counter; i++){
                DrawTextEx(font, m_top_score_text[i], {326, 440 + (i*20)}, 14, 2, light_green);
            }
        }

    switch (m_state){
        case state_pause:
    //if (paused){
            options.draw();
            break;
    //}else{
    //
        case state_run:
            grid.draw();
            current_block.draw(11, 11);
            switch (next_block.id) {
            case 3:
                next_block.draw(255, 290);
                break;
            case 4:
                next_block.draw(255, 280);
                break;
            default:
                next_block.draw(270, 270);
                break;
            }
            break;
        case state_over:
            options.draw_score_enter(score);
            break;
    }
}

void Game::handle_options(){
    if (music_selector != option_parameters->theme_nr){
        if (option_parameters->theme_nr < 3){
            stop_music(music_selector);
            music_selector = option_parameters->theme_nr;
            play_music(music_selector);
            pause_music(music_selector);
        }
    }
    m_sound_muted = option_parameters->sound_muted;
    m_difficulty_level = option_parameters->difficulty_level;
}

void Game::play_sound(Sound sound){
    if (!m_sound_muted){
        PlaySound(sound);
    }
}

void Game::play_music(uint8_t theme){
    if (theme < 3){
        PlayMusicStream(musics[theme]);
    }
}

void Game::stop_music(uint8_t theme){
    if (theme < 3){
        StopMusicStream(musics[theme]);
    }
}

void Game::pause_music(uint8_t theme){
    if (theme < 3){
        PauseMusicStream(musics[theme]);
    }
}

void Game::resume_music(uint8_t theme){
    if (theme < 3){
        ResumeMusicStream(musics[theme]);
    }
}

void Game::handle_input() {
    int keyPressed = GetKeyPressed();
    if (game_over && keyPressed != 0) {
        //game_over = false;
        //reset();
    }
    switch (m_state){
        case state_pause:
    //if (paused){
            switch (keyPressed) {
                case KEY_UP:
                    options.menu_up();
                    break;
                case KEY_DOWN:
                    options.menu_down();
                    break;
                case KEY_ENTER:
                    option_parameters = options.menu_enter();
                    handle_options();
                    break;
                case KEY_BACKSPACE:
                    options.menu_back();
                    break;
                case KEY_SPACE:
                    paused = false;
                    m_state = state_run;
                    play_sound(unpause_sound);
                    if (music_selector < 3){
                        resume_music(music_selector);
                    }
                    break;
            }
            break;

        case state_run:
    //}else{
            switch (keyPressed) {
                case KEY_LEFT:
                    move_block_left();
                    break;
                case KEY_RIGHT:
                    move_block_right();
                    break;
                case KEY_DOWN:
                    update_score(0, 1);
                    break;
                case KEY_UP:
                case KEY_R:
                    rotate_block_r();
                    break;
                case KEY_T:
                    rotate_block_l();
                    break;
                case KEY_SPACE:
                    paused = true;
                    m_state = state_pause;
                    if (music_selector < 3){
                        pause_music(music_selector);
                    }
                    play_sound(pause_sound);
                    break;
            }

            if (IsKeyDown(KEY_DOWN)){
                move_block_down();
            }
            break;
        case state_over:
            int key = GetCharPressed();
            if (key != 0){
                options.set_sign(key);
            }
            if (IsKeyPressed(KEY_ENTER)){
                options.submit_score();
                reset();
            }
            break;

    }

    //if (IsKeyDown(KEY_LEFT)){
    //    move_block_left();
    //}
    //if (IsKeyDown(KEY_RIGHT)){
    //    move_block_right();
    //}
}

void Game::move_block_left() {
    if (is_running()) {
        current_block.move(0, -1);
        if (is_block_outside() || block_fits() == false) {
            current_block.move(0, 1);
        }
    }
}

void Game::move_block_right() {
    if (is_running()) {
        current_block.move(0, 1);
        if (is_block_outside() || block_fits() == false) {
            current_block.move(0, -1);
        }
    }
}

void Game::move_block_down() {
    if (is_running()) {
        current_block.move(1, 0);
        if (is_block_outside() || block_fits() == false) {
            current_block.move(-1, 0);
            lock_block();
        }
    }
}

bool Game::is_block_outside() {
    std::vector<position> tiles = current_block.get_cell_positions();
    for (position item : tiles) {
        if (grid.is_cell_outside(item.row, item.column)) {
            return true;
        }
    }
    return false;
}

void Game::rotate_block_r() {
    if (is_running()) {
        current_block.rotate();
        if (is_block_outside() || block_fits() == false) {
            current_block.undo_rotate();
        } else {
            play_sound(rotate_sound);
        }
    }
}


void Game::rotate_block_l() {
    if (is_running()) {
        current_block.undo_rotate();
        if (is_block_outside() || block_fits() == false) {
            current_block.rotate();
        } else {
            play_sound(rotate_sound);
        }
    }
}

void Game::over(){
    if (m_state != state_over){
        game_over = true;
        m_state = state_over;
        stop_music(music_selector);
        play_sound(game_over_sound);
    }
}

void Game::lock_block() {
    std::vector<position> tiles = current_block.get_cell_positions();
    for (position item : tiles) {
        grid.cell_grid[item.row][item.column] = current_block.id;
    }
    current_block = next_block;
    if (block_fits() == false) {
        over();
        //game_over = true;
        //stop_music(music_selector);
        //play_sound(game_over_sound);
    }
    next_block = get_random_block();
    uint8_t rows_cleared = grid.clear_full_rows();
    if (rows_cleared > 0) {
        play_sound(clear_sounds[rows_cleared - 1]);
        update_score(rows_cleared, 0);
        if (m_difficulty_level == 3){
            m_difficulty_factor[3] /= 1.02;
        }
    }
}

bool Game::block_fits() {
    std::vector<position> tiles = current_block.get_cell_positions();
    for (position item : tiles) {
        if (grid.is_cell_empty(item.row, item.column) == false) {
            return false;
        }
    }
    return true;
}

void Game::reset() {
    m_state = state_run;
    grid.init();
    blocks = get_all_blocks();
    current_block = get_random_block();
    next_block = get_random_block();
    score = 0;
    play_music(music_selector);
    m_difficulty_factor[3] = 0.5;
    m_top_score_calculated = false;
}

void Game::update_score(int lines_cleared, int move_down_points) {
    switch (lines_cleared) {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 1000;
        break;
    default:
        break;
    }

    score += move_down_points;
}

bool Game::is_running(){
    return m_state == state_run;
}

bool Game::is_over(){
    return m_state == state_over;
}

bool Game::is_paused(){
    return m_state == state_pause;
}

double Game::get_difficulty_factor(){
    return m_difficulty_factor[m_difficulty_level];
}


