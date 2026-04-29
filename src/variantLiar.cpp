#include "variantLiar.h"

bool VariantLiar::is_valid_tile(const int x, const int y, const Board &board) const 
{
    int mines = 0;
    int unknowns = 0;

    for (auto t : board.neighbors(x, y)) 
    {
        if (t->is_mine()) 
        {
            mines++;
            if (mines > board.neighboring_mines(x, y) + 1) {
                return false;
            }
        } 
        else if (t->is_unknown())
        {
            unknowns++;
        }
    }

    if (mines == board.neighboring_mines(x, y) + 1 || mines == board.neighboring_mines(x, y) + 1) {
        return true;
    }

    if (unknowns >= (mines + board.neighboring_mines(x, y) - 1)) {
        return true;
    }

    return false;
};