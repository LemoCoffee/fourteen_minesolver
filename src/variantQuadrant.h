#ifndef QUADRANT_H
#define QUADRANT_H

#include "variantBasic.h"

class VariantQuadrant : public VariantBasic
{
public:
    bool is_valid_board(const Board &board) const override;
};

#endif
