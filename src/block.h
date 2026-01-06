#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colours.h"

class Block {
    public:
        Block();
        void draw(int offset_x, int offset_y);
        void move(int rows, int columns);
        std::vector<position> get_cell_positions();
        void rotate();
        void undo_rotate();
        int id;
        std::map<int, std::vector<position>> cells;

    private:
        int cell_size;
        int m_rotation_state;
        std::vector<Color> colours;
        int m_row_offset;
        int m_column_offset;
};


