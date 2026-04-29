#ifndef BASIC_H
#define BASIC_H

#include "variant.h"

class VariantBasic : public Variant
{
public:
    std::vector<Board> get_possibilities(const int x, const int y, const Board &board) override;
    std::vector<Board> get_possibilities(const Board &board) override;

    bool is_valid_tile(const int x, const int y, const Board &board) const override;
    bool is_valid_board(const Board &board) const override;
};

#endif
