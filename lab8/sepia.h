//
// Created by Sergey Fedorov on 12/18/20.
//

#pragma once

#include "bmp.h"

#define C_1_1 .393f
#define C_1_2 .769f
#define C_1_3 .189f

#define C_2_1 .349f
#define C_2_2 .686f
#define C_2_3 .168f

#define C_3_1 .272f
#define C_3_2 .534f
#define C_3_3 .131f


void sse_sepia(struct bmp_image* image);

void naive_sepia(struct bmp_image* image);