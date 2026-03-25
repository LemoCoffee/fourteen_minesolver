#ifndef BASIC_H
#define BASIC_H

#include <vector>
#include "board.h"

std::vector<Board> solve(const Board& puzzle);
bool is_valid_tile(const int x, const int y, const Board& board);
bool is_valid_board(const Board& board);

#endif
