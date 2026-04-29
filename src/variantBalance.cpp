#include "variantBalance.h"

bool VariantBalance::is_valid_board(const Board &board) const
{
    int mine_count = board.mine_count() / board.width();

    for (int x = 0; x < board.width(); x++)
    {
        int y_count = 0;
        for (int y = 0; y < board.height(); y++)
        {
            int  x_count = 0;
            for (int i = 0; x < board.width(); i++)
            {
                if (board[i][y].is_empty()) {
                    x_count++;
                }
            }
            if (x_count < mine_count) {
                return false;
            }
            if (board[x][y].is_empty()) {
                y_count++;
            }
        }
        
        if (y_count < mine_count) {
            return false;
        }
    }

    return VariantBasic::is_valid_board(board);
}