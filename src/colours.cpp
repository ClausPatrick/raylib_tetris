#include "colours.h"


const Color dark_grey    = {26,  31,  40,  255};
const Color green        = {47,  200, 43,  255};
const Color dark_green   = {10,  100, 50,  255};
const Color red          = {200, 38,  20,  255};
const Color orange       = {200, 100, 20,  255};
const Color yellow       = {200, 200, 10,  255};
const Color magenta      = {160, 0,   240, 255};
const Color cyan         = {20,  200, 200, 255};
const Color blue         = {10,  80,  210, 255};
const Color light_blue   = {50,  60,  140, 255};
const Color dark_blue    = {10,  60,  100, 255};
const Color light_green  = {50,  250, 80,  255};

std::vector<Color> get_cell_colours(){
     return {dark_grey, green, red, orange, yellow, magenta, cyan, blue, light_blue};
}


