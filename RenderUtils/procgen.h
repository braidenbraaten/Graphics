#pragma once

#include "globjects.h"
//Generate grid
//                               how big is the grid
Geometry genGrid(unsigned sqr, float dim);

//make some noise
//                size of tex, num of patterns
Texture genNoise(unsigned sqr, unsigned octaves);