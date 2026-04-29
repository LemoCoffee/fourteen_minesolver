#ifndef TRIPLET_H
#define TRIPLET_H

#include "variantBasic.h"

class VariantTriplet : public VariantBasic
{
public:
    bool is_valid_board(const Board &board) const override;
};

#endif
