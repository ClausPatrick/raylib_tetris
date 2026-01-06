#include "grid.h"



Grid::Grid(){
    m_row_count = 20;
    m_column_count = 10;
    m_cell_size = 30;
    init();
    m_colours = get_cell_colours();  // From colours.h
}


void Grid::init(){
    for (int r=0; r<m_row_count; r++){
        for (int c=0; c<m_column_count; c++){
            cell_grid[r][c] = 0;
        }
    }
}

void Grid::print(){
    for (int r=0; r<m_row_count; r++){
        for (int c=0; c<m_column_count; c++){
            std::cout<<cell_grid[r][c]<<' ';
        }
        std::cout<<'\n';
    }
}

void Grid::draw(){
    for (int r=0; r<m_row_count; r++){
        for (int c=0; c<m_column_count; c++){
            int cell_value = cell_grid[r][c];
            DrawRectangle(c*m_cell_size+11, r*m_cell_size+11, m_cell_size-1,  m_cell_size-1,  m_colours[cell_value]);
        }
    }
}

bool Grid::is_cell_outside(int row, int column) {
    if (row >= 0 && row < m_row_count && column >= 0 && column < m_column_count)
    {
        return false;
    }
    return true;
}

bool Grid::is_cell_empty(int row, int column) {
    if (cell_grid[row][column] == 0) {
        return true;
    }
    return false;
}

uint8_t Grid::clear_full_rows() {
    uint8_t completed = 0;
    for (int row = m_row_count - 1; row >= 0; row--) {
        if (is_row_full(row)) {
            clear_row(row);
            completed++;
        }
        else if (completed > 0) {
            move_row_down(row, completed);
        }
    }
    return completed;
}

bool Grid::is_row_full(int row) {
    for (int column = 0; column < m_column_count; column++) {
        if (cell_grid[row][column] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::clear_row(int row) {
    for (int column = 0; column < m_column_count; column++) {
        cell_grid[row][column] = 0;
    }
}

void Grid::move_row_down(int row, int m_row_count) {
    for (int column = 0; column < m_column_count; column++) {
        cell_grid[row + m_row_count][column] = cell_grid[row][column];
        cell_grid[row][column] = 0;
    }
}

