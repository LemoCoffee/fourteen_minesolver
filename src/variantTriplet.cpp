#include "variantTriplet.h"

bool VariantTriplet::is_valid_board(const Board &board) const
{
    for (int x = 0; x < board.width(); x++)
    {
        for (int y = 0; y < board.height(); y++)
        {
            if (board[x][y].is_empty()) {
                continue;
            }
            
            if (x < board.width() - 2) {
                if (board[x][y].is_mine() && board[x + 1][y].is_mine() && board[x + 2][y].is_mine()) {
                    return false;
                }
            }

            if (y < board.height() - 2) {
                if (board[x][y].is_mine() && board[x][y + 1].is_mine() && board[x][y + 1].is_mine()) {
                    return false;
                }

                if (x >= 2) {
                    if (board[x][y].is_mine() && board[x - 1][y + 1].is_mine() && board[x - 2][y + 1].is_mine()) {
                        return false;
                    }
                }

                if (x < board.width() - 2) {
                    if (board[x][y].is_mine() && board[x + 1][y + 1].is_mine() && board[x + 2][y + 1].is_mine()) {
                        return false;
                    }
                }
            }
        }
    }

    return VariantBasic::is_valid_board(board);
}