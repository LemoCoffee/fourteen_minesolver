#include "variantDual.h"

bool VariantDual::is_valid_board(const Board &board) const
{
    for (int x = 0; x < board.width(); x++)
    {
        for (int y = 0; y < board.height(); y++)
        {
            if (board[x][y].is_empty()) {
                continue;
            }
            
            auto connected = board.orthogonal_coords(x, y);

            std::pair<int, int> *pair = nullptr;

            for (auto n : connected) {
                if (board[n].is_mine()) {
                    if (pair == nullptr) {
                        pair = &n;
                    } else {
                        return false;
                    }
                }
            }

            connected = board.orthogonal_coords(pair->first, pair->second);

            for (auto n : connected) {
                if (board[n].is_mine()) {
                    if (n.first != x || n.second != y) {
                        return false;
                    }
                }
            }
        }
    }

    return VariantBasic::is_valid_board(board);
}

