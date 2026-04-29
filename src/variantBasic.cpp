#include "variantBasic.h"



std::vector<Board> VariantBasic::get_possibilities(const Board &board) {
    /*
    std::vector<Board> possibilities = {};

    for (int x = 0; x < puzzle.width(); x++)
    {
        for (int y = 0; y < puzzle.height(); y++)
        {
            auto p = get_possibilities(x, y, puzzle);
            for (const auto &b : p)
            {
                if (is_valid_board(b))
                {
                    possibilities.emplace_back(b);
                }
            }
        }
    }    
    */
    auto possibilities = global_brute_force(board);

    return possibilities;
}

std::vector<Board> VariantBasic::get_possibilities(const int x, const int y, const Board &board)
{
    std::vector<Board> possibilities = std::vector<Board>();

    if (!board.has_tile(x, y) || board[x][y] == Tile::unknown || board[x][y] == Tile::mine)
    {
        possibilities.emplace_back(Board(board));
        return possibilities;
    }

    std::vector<std::pair<int, int>> neighbor_coords = board.neighbor_coords(x, y);

    std::vector<std::pair<int, int>> unknown_neighbors = {};
    for (const std::pair<int, int> &pos : neighbor_coords)
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

    for (unsigned int mask = (2 << unflagged_mines) - 1; mask < (1U << num_unknown); mask++)
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

bool VariantBasic::is_valid_tile(const int x, const int y, const Board &board) const
{
    const Tile &tile = board[x][y];

    if (tile.is_mine() || tile.is_unknown() || tile.value == Tile::empty.value)
    {
        return true;
    }

    int mine_count = 0;
    int unknown_count = 0;
    int neighboring_mines = board.neighboring_mines(x, y);

    for (const auto &n : board.neighbor_coords(x, y))
    {
        if (board[n].is_mine())
        {
            mine_count++;
        }
        if (board[n].is_unknown())
        {
            unknown_count++;
        }

        if (mine_count > neighboring_mines)
        {
            return false;
        }
    }

    return (mine_count + unknown_count >= neighboring_mines);
}

bool VariantBasic::is_valid_board(const Board &board) const
{
    int placed_mines = 0;
    bool has_unknowns = false;

    count_evaluation();

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
                placed_mines++;
            }
            if (board[x][y].is_unknown())
            {
                has_unknowns = true;
            }
        }
    }

    // If there are no unknown tiles, mine count must match exactly.
    // Otherwise, the current mine count must not exceed the total allowed mines.
    // This ensures that a fully revealed board is only valid if the mine count is exact,
    // but partially revealed boards are valid as long as they do not exceed the mine limit.

    if (!has_unknowns)
    {
        return placed_mines == board.mine_count();
    }
    return placed_mines <= board.mine_count();
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
                for (Tile *t : board.neighbors(x, y))
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