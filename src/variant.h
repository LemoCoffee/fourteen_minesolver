#ifndef VARIANT_H
#define VARIANT_H

#include "board.h"

class IVariant
{
public:
    virtual std::vector<Board> solve(const Board &puzzle);
    virtual std::vector<Board> get_possibilites(const int x, const int y, const Board &board);

    virtual bool is_valid_tile(const int x, const int y, const Board &board);
    virtual bool is_valid_board(const Board &board);
};

// I want functions to be inherited and implemented by children, but I don't want variants to be instantiated or contain any info

#endif