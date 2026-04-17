#include "variantBasic.h"

Board VariantBasic::collapse_possibilities(std::vector<Board> possibilities)
{
    bool found_board = false;
    Board output = Board(possibilities[0]);
    for (const auto &p : possibilities)
    {

        if (is_valid_board(p))
        {
            if (!found_board)
            {
                output = Board(p);
                found_board = true;
            }
            else
            {
                output = Board::join(output, p);
            }
        }
    }
    return output;
}

Board VariantBasic::solve(const Board &puzzle)
{
    reset_statistics();
    std::vector<Board> possibilities = {};

    for (int x = 0; x < puzzle.width(); x++)
    {
        for (int y = 0; y < puzzle.height(); y++)
        {
            auto p = get_possibilites(x, y, puzzle);
            for (const auto &b : p)
            {
                if (is_valid_board(b))
                {
                    possibilities.emplace_back(b);
                }
            }
        }
    }

    auto output = global_brute_force(puzzle);

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

Board VariantBasic::global_brute_force(const Board &board)
{
    auto unknown_coords = board.coordinates_flagged_as(Tile::unknown_flag);
    int remaining_mines = std::max(0, board.mine_count() - board.tiles_flagged_as(Tile::mine_flag));

    Board mutable_board = Board(board);
    auto possibilities = VariantBasic::global_brute_force_helper(mutable_board, unknown_coords, 0, remaining_mines);

    if (possibilities.size() == 0)
    {
        return board;
    }

    return collapse_possibilities(possibilities);
}

// Recursive method
std::vector<Board> VariantBasic::global_brute_force_helper(Board &board, const std::vector<std::pair<int, int>> &unknowns, int current_pos, int remaining_mines)
{
    std::vector<Board> output = {};

    if (remaining_mines == 0)
    {
        if (current_pos == unknowns.size())
        {
            output.emplace_back(board);
        }
        else
        {
            // Save original tiles to backtrack later
            std::vector<Tile> original_tiles;
            for (int i = current_pos; i < unknowns.size(); i++)
            {
                original_tiles.push_back(board[unknowns[i]]);
                board[unknowns[i]] = Tile::empty;
            }
            if (is_valid_board(board))
            {
                output.emplace_back(board);
            }
            // Backtrack
            for (int i = current_pos; i < unknowns.size(); i++)
            {
                board[unknowns[i]] = original_tiles[i - current_pos];
            }
        }

        return output;
    }

    if (current_pos == unknowns.size())
    {
        return output;
    }

    // Save original tile to backtrack
    Tile original_tile = board[unknowns[current_pos]];

    board[unknowns[current_pos]] = Tile::empty;
    if (is_valid_board(board))
    {
        auto without_mine = global_brute_force_helper(board, unknowns, current_pos + 1, remaining_mines);
        output.insert(output.end(), without_mine.begin(), without_mine.end());
    }

    board[unknowns[current_pos]] = Tile::mine;
    if (is_valid_board(board))
    {
        auto with_mine = global_brute_force_helper(board, unknowns, current_pos + 1, remaining_mines - 1);
        output.insert(output.end(), with_mine.begin(), with_mine.end());
    }

    // Backtrack
    board[unknowns[current_pos]] = original_tile;

    return output;
}

bool VariantBasic::is_valid_tile(const int x, const int y, const Board &board) const
{
    const Tile &tile = board[x][y];

    if (tile.is_mine() || tile.is_unknown() || tile.is_empty())
    {
        return true;
    }

    int mine_count = 0;
    int unknown_count = 0;
    int neighboring_mines = board.neighboring_mines(x, y);

    for (const auto &n : board.coordinate_neighbors_of(x, y))
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