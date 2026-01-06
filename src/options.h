#pragma once
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <string>
#include <string.h>
#include "colours.h"
#include "scoring.h"




struct Menu_Node{
    std::string label;
    bool enabled;
    std::vector<Menu_Node> children;
    std::function<void()> action = nullptr;
};



struct Option_Parameters{
    uint8_t theme_nr;
    bool sound_muted;
    uint8_t difficulty_level;
};

class Options{
    public:
        Options();
        ~Options();
        Options(const Options&) = delete;
        Options& operator=(const Options&) = delete;
        Options(Options&&) = delete;
        Options& operator=(Options&&) = delete;
        void draw();
        void draw_score_enter(size_t score);
        void submit_score();
        void set_sign(int key);
        void menu_up();
        void menu_down();
        Option_Parameters*  menu_enter();
        void menu_back();
        int get_ranking(size_t rank, size_t* score, char* name, char* date);
    private:
        Menu_Node m_menu_root;
        Menu_Node* m_current_menu;
        size_t m_selected_menu;
        Font font;
        std::vector<Menu_Node*> menu_stack;
        Option_Parameters m_op;
        size_t m_score;
        char m_sign[4];
        uint8_t m_sign_cursor;
        Scoring scorer;
        bool show_top_scores;
};
