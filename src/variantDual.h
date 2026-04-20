#ifndef DUAL_H
#define DUAL_H

#include "variantBasic.h"

class VariantDual : public VariantBasic
{
public:
    bool is_valid_board(const Board &board) const override;
};

#endif
