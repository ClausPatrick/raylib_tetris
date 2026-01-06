#include "options.h"


Options::Options() :
    m_menu_root({
        "   Options", false,
        {
            { "Music", false, {
                { "Theme A", true,  {}, [this](){ m_op.theme_nr = 0;} },
                { "Theme B", false,  {}, [this](){ m_op.theme_nr = 1;} },
                { "Theme C", false,  {}, [this](){ m_op.theme_nr = 2;} },
                { "Off", false, {}, [this](){ m_op.theme_nr = 3;;} },
            }},
            { "Sound", false, {
                { "On", true,  {}, [this](){ m_op.sound_muted = 1;} },
                { "Off",false,  {}, [this](){ m_op.sound_muted = 0;} },
            }},
            { "Top Score", false, {
                { "Show",  false,{}, [this](){ show_top_scores = true;} },
                { "Clear", false, {}, [this](){ printf("Are you sure?\n");} },
            }},
            { "Difficulty", false, {
                { "Slow", true, {}, [this](){ m_op.difficulty_level = 0;} },
                { "Medium", false, {}, [this](){ m_op.difficulty_level = 1;} },
                { "Fast", false, {}, [this](){ m_op.difficulty_level = 2;} },
                { "Progressive", false,  {}, [this](){ m_op.difficulty_level = 3;} },
            }},
        }
    }),
    m_current_menu(&m_menu_root),
    m_selected_menu(0),
    font(LoadFontEx("Font/monogram.ttf", 64, 0, 0)),
    m_op({0, false, 0}),
    show_top_scores(false),
    m_sign_cursor(0) {
        scorer.fetch_scores();
        for (size_t i=0; i<3; i++){
            m_sign[i] = '_';
        }
        m_sign[3] = '\0';
    }

Options::~Options(){ 
    scorer.dump_scores();
}



void Options::draw(){
    char buffer[12];
    DrawRectangleRounded({20, 20, 240, 590}, 0.3, 6, dark_green);
    DrawTextEx(font, "    Options:", {30, 30}, 24, 2, green);
    char sym;
    
    for (size_t i=0; i<m_current_menu->children.size(); i++){
        if (i==m_selected_menu){
            sym = '>';
        }else{
            sym = ' ';
        }
      Menu_Node* child = &m_current_menu->children.at(i);
      sprintf(buffer, "%c%s", sym, (m_current_menu->children.at(i).label).c_str());
      if (child->enabled == true){
          DrawTextEx(font, buffer, {30, 60 + i*20}, 18, 2, light_green);
      }else{
          DrawTextEx(font, buffer, {30, 60 + i*20}, 16, 2, green);
      }
    }

    if (show_top_scores){

        char score_text[64];
        size_t top_score;
        char top_name[4];
        char top_date[16];
        for (size_t i=0; i<15; i++){
            int r = get_ranking(i, &top_score, top_name, top_date);
            if (r==0){
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

                sprintf(score_text, "%s, %ld, %s-%s-%s", top_name, top_score, tdy, tdm, tdd);
                DrawTextEx(font, "Top scores:", {60, 110}, 16, 2, light_green);
                DrawTextEx(font, score_text, {40, 140 + (i*20)}, 14, 2, light_green);
            }else{
                break;
            }
        }
    }
        

}

void Options::submit_score(){
    scorer.submit(m_score, m_sign);
    //printf("score: %ld, sign: %s\n", m_score, m_sign);
}

void Options::draw_score_enter(size_t score){
    m_score = score;
    DrawRectangleRounded({20, 20, 240, 590}, 0.3, 6, dark_green);
    DrawTextEx(font, "  Enter your sign:", {30, 30}, 24, 2, green);
    DrawTextEx(font, m_sign, {60, 90}, 24, 2, green);
    char score_buffer[22];
    sprintf(score_buffer, "Score: %ld ", m_score);
    DrawTextEx(font, score_buffer, {30, 220}, 24, 2, green);
}

void Options::set_sign(int key){
    m_sign[m_sign_cursor] = key;
    m_sign_cursor = (m_sign_cursor + 1) % 3;
}



void Options::menu_up(){
    m_selected_menu = (m_selected_menu - 1 + m_current_menu->children.size()) % m_current_menu->children.size();
}

void Options::menu_down(){
    m_selected_menu = (m_selected_menu + 1) % m_current_menu->children.size();
}

Option_Parameters* Options::menu_enter(){
    Menu_Node& menu = m_current_menu->children[m_selected_menu];
    if (!menu.children.empty()){
        menu_stack.push_back(m_current_menu);
        m_current_menu = &menu;
        m_selected_menu = 0;
    }else if(menu.action){
        menu.action();
        for (size_t i = 0; i<m_current_menu->children.size(); i++){
            m_current_menu->children.at(i).enabled = false;
        }
        menu.enabled = true;
    }
    return &m_op;
}

void Options::menu_back(){
    show_top_scores = false;
    if (!menu_stack.empty()){
        m_current_menu = menu_stack.back();
        menu_stack.pop_back();
        m_selected_menu = 0;
    }
}


int Options::get_ranking(size_t rank, size_t* score, char* name, char* date){
    return scorer.get_ranking(rank, score, name, date);
}





