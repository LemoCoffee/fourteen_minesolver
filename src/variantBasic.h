#ifndef BASIC_H
#define BASIC_H

#include "variant.h"

class VariantBasic
{
public:
    std::vector<Board> solve(const Board &puzzle);
    std::vector<Board> get_possibilites(const int x, const int y, const Board &board);

    bool is_valid_tile(const int x, const int y, const Board &board);
    bool is_valid_board(const Board &board);
};

#endif
