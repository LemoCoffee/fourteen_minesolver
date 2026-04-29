#ifndef BALANCE_H
#define BALANCE_H

#include "variantBasic.h"

class VariantBalance : public VariantBasic
{
public:
    bool is_valid_board(const Board &board) const override;
};

#endif
