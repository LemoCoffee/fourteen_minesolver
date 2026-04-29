#ifndef LIAR_H
#define LIAR_H

#include "variantBasic.h"

class VariantLiar : public VariantBasic
{
public:
    bool is_valid_tile(const int x, const int y, const Board &board) const override;
};

#endif
