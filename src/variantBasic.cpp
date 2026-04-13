#include <vector>
#include <algorithm>
#include <cmath>
#include "variantBasic.h"

std::vector<Board> VariantBasic::solve(const Board &puzzle)
{
    std::vector<Board> output = {puzzle};
    return output;
}

std::vector<Board> VariantBasic::get_possibilites(const int x, const int y, const Board &board)
{
    std::vector<Board> possibilities = std::vector<Board>();

    if (!board.has_tile(x, y) || board[x][y] == Tile::unknown || board[x][y] == Tile::mine)
    {
        possibilities.emplace_back(Board(board));
        return possibilities;
    }

    std::vector<std::pair<int, int>> neighbor_coords = board.coordinate_neighbors_of(x, y);
    std::vector<std::pair<int, int>> unknown_neighbors = {};
    /*std::copy_if(neighbor_coords.begin(), neighbor_coords.end(), std::back_inserter(unknown_neighbors), [board](std::pair<int, int> pos)
                 { return board[pos].is_unknown(); });*/
    for (std::pair<int, int> pos : neighbor_coords)
    {
        if (board[pos].is_unknown())
        {
            unknown_neighbors.emplace_back(pos);
        }
    }

    int neighboring_mines = board.neighboring_mines(x, y);
    int neighboring_flagged = board.neighboring_flagged_as(x, y, Tile::mine_flag);
    int unflagged_mines = neighboring_mines - neighboring_flagged;

    int num_unknown = unknown_neighbors.size();

    for (unsigned int mask = pow(2, unflagged_mines) - 1; mask < (1U << num_unknown); mask++)
    {
        if (__builtin_popcount(mask) == unflagged_mines)
        {
            Board board_permutation = Board(board);

            for (int j = 0; j < num_unknown; j++)
            {
                if (mask & (1U << j))
                {
                    board_permutation[unknown_neighbors[j]] = Tile::mine;
                }
                else
                {
                    board_permutation[unknown_neighbors[j]] = Tile::empty;
                }
            }

            possibilities.emplace_back(board_permutation);
        }
    }

    return possibilities;
}

bool VariantBasic::is_valid_tile(const int x, const int y, const Board &board)
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

bool VariantBasic::is_valid_board(const Board &board)
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