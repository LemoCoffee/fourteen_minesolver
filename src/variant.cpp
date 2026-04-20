#include "variant.h"

Board IVariant::solve(const Board &puzzle)
{
    reset_statistics();
    
    auto output = get_possibilities(puzzle);

    return collapse_possibilities(output);
}

Board IVariant::collapse_possibilities(const std::vector<Board> &possibilities)
{
    bool found_board = false;
    Board output = Board(possibilities[0]);
    for (const auto &p : possibilities)
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
    return output;
}

std::vector<Board> IVariant::global_brute_force(const Board &board)
{
    auto unknown_coords = board.coordinates_flagged_as(Tile::unknown_flag);
    int remaining_mines = std::max(0, board.mine_count() - board.tiles_flagged_as(Tile::mine_flag));

    Board mutable_board = Board(board);
    auto possibilities = global_brute_force_helper(mutable_board, unknown_coords, 0, remaining_mines);

    if (possibilities.size() == 0)
    {
        possibilities.emplace_back(board);
    }

    return possibilities;
}

std::vector<Board> IVariant::global_brute_force_helper(Board &board, const std::vector<std::pair<int, int>> &unknowns, int current_pos, int remaining_mines)
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