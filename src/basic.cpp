#include <vector>
#include "basic.h"

std::vector<Board> solve(const Board &puzzle)
{
    std::vector<Board> output = {puzzle};
    return output;
}

bool is_valid_tile(const int x, const int y, const Board &board)
{
    const Tile &tile = board[x][y];

    if (tile.is_mine() || tile.is_unknown())
    {
        return true;
    }

    int mine_count = 0;
    int unknown_count = 0;

    for (int nx = x - 1; nx <= x + 1; nx++)
    {
        if (!board.has_tile(nx, 0))
        {
            continue;
        }

        for (int ny = y - 1; ny <= y + 1; ny++)
        {
            if (!board.has_tile(nx, ny) || (ny == y && nx == x))
            {
                continue;
            }
            if (board[nx][ny].is_mine())
            {
                mine_count++;
            }
            if (board[nx][ny].is_unknown())
            {
                unknown_count++;
            }
        }

        if (mine_count > (tile.value - '0'))
        {
            return false;
        }
    }

    return (mine_count + unknown_count >= (tile.value - '0'));
}

bool is_valid_board(const Board &board)
{
    int mine_count = 0;

    for (int x = 0; x < board.width(); x++)
    {
        for (int y = 0; y < board.height(); y++)
        {
            if (!is_valid_tile(x, y, board))
            {
                return false;
            }
            if (board[x][y].is_mine())
            {
                mine_count++;
            }
        }
    }

    return mine_count < board.mine_count();
}

bool reveal_guarantees(Board &board)
{
    bool changed = false;

    for (int x = 0; x < board.width(); x++)
    {
        for (int y = 0; y < board.height(); y++)
        {
            if (board.tile_possibility_score(x, y) == 1)
            {
                for (Tile *t : board.neighbors_of(x, y))
                {
                    if (t->flags & Tile::unknown_flag)
                    {
                        t->flags |= Tile::mine_flag;
                        t->flags &= ~(Tile::unknown_flag);
                        changed = true;
                    }
                }
            }
        }
    }

    return changed;
}