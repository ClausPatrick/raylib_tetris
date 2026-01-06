#include "blocks.h"

l_Block::l_Block() {
        id = 1;
        cells[0] = {position(0, 2), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(1, 1), position(2, 1), position(2, 2)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 0)};
        cells[3] = {position(0, 0), position(0, 1), position(1, 1), position(2, 1)};
        move(0, 3);
}

j_Block::j_Block() {
        id = 2;
        cells[0] = {position(0, 0), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(0, 2), position(1, 1), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 2)};
        cells[3] = {position(0, 1), position(1, 1), position(2, 0), position(2, 1)};
        move(0, 3);
}

i_Block::i_Block() {
        id = 3;
        cells[0] = {position(1, 0), position(1, 1), position(1, 2), position(1, 3)};
        cells[1] = {position(0, 2), position(1, 2), position(2, 2), position(3, 2)};
        cells[2] = {position(2, 0), position(2, 1), position(2, 2), position(2, 3)};
        cells[3] = {position(0, 1), position(1, 1), position(2, 1), position(3, 1)};
        move(-1, 3);
}

o_Block::o_Block() {
        id = 4;
        cells[0] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        move(0, 4);
}

s_Block::s_Block() {
        id = 5;
        cells[0] = {position(0, 1), position(0, 2), position(1, 0), position(1, 1)};
        cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 2)};
        cells[2] = {position(1, 1), position(1, 2), position(2, 0), position(2, 1)};
        cells[3] = {position(0, 0), position(1, 0), position(1, 1), position(2, 1)};
        move(0, 3);
}

t_Block::t_Block() {
        id = 6;
        cells[0] = {position(0, 1), position(1, 0), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 1)};
        cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 1)};
        move(0, 3);
}

z_Block::z_Block() {
        id = 7;
        cells[0] = {position(0, 0), position(0, 1), position(1, 1), position(1, 2)};
        cells[1] = {position(0, 2), position(1, 1), position(1, 2), position(2, 1)};
        cells[2] = {position(1, 0), position(1, 1), position(2, 1), position(2, 2)};
        cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 0)};
        move(0, 3);
}
