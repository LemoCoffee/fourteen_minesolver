#ifndef VARIANT_H
#define VARIANT_H

#include "board.h"

class IVariant
{
public:
    virtual ~IVariant() = default;

    virtual Board solve(const Board &puzzle) = 0;
    virtual std::vector<Board> get_possibilites(const int x, const int y, const Board &board) = 0;

    virtual bool is_valid_tile(const int x, const int y, const Board &board) const = 0;
    virtual bool is_valid_board(const Board &board) const = 0;
};

#endif