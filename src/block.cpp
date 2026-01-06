#include "block.h"

Block::Block()
{
    cell_size = 30;
    m_rotation_state = 0;
    colours = get_cell_colours();
    m_row_offset = 0;
    m_column_offset = 0;
}

void Block::draw(int offset_x, int offset_y)
{
    std::vector<position> tiles = get_cell_positions();
    for (position item : tiles)
    {
        DrawRectangle(item.column * cell_size + offset_x, item.row * cell_size + offset_y, cell_size - 1, cell_size - 1, colours[id]);
    }
}

void Block::move(int rows, int columns) {
    m_row_offset += rows;
    m_column_offset += columns;
}

std::vector<position> Block::get_cell_positions() {
    std::vector<position> tiles = cells[m_rotation_state];
    std::vector<position> moved_tiles;
    for (position item : tiles) {
        position new_position = position(item.row + m_row_offset, item.column + m_column_offset);
        moved_tiles.push_back(new_position);
    }
    return moved_tiles;
}

void Block::rotate() {
    m_rotation_state++;
    if (m_rotation_state == (int)cells.size()) {
        m_rotation_state = 0;
    }
}

void Block::undo_rotate() {
    m_rotation_state--;
    if (m_rotation_state == -1) {
        m_rotation_state = cells.size() - 1;
    }
}
