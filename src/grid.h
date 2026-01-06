#pragma once
#include <iostream>
#include <cstdint>
#include <vector>
#include <raylib.h>
#include "colours.h"

//
//class Grid{
//    public:
//        Grid();
//        int cells[20][10];
//        void init();
//        void print();
//        void draw();
//    private:
//        int m_row_count;
//        int m_column_count;
//        int m_cell_size;
//        std::vector<Color> m_colours;
//};
//

class Grid {
    public:
        Grid();
        void init();
        void print();
        void draw();
        bool is_cell_outside(int row, int column);
        bool is_cell_empty(int row, int column);
        uint8_t clear_full_rows();
        int cell_grid[20][10];

    private:
        bool is_row_full(int row);
        void clear_row(int row);
        int m_row_count;
        int m_column_count;
        int m_cell_size;
        void move_row_down(int row, int m_row_count);
        std::vector<Color> m_colours;
};
