#include "variantQuadrant.h"

bool VariantQuadrant::is_valid_board(const Board &board) const
{

    for (int x = 0; x < board.width() - 1; x++)
    {
        for (int y = 0; y < board.height() - 1; y++)
        {
            if ((
                    board[x][y].is_empty() &&
                    board[x + 1][y].is_empty() &&
                    board[x][y + 1].is_empty() &&
                    board[x + 1][y + 1].is_empty()))
            {
                return false;
            }
        }
    }

    return VariantBasic::is_valid_board(board);
}