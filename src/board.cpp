#include "board.h"
#include <stdexcept>

bool Board::has_tile(int x, int y) const
{
    return x >= 0 && x < width() && y >= 0 && y < height();
}

bool Board::is_mine(int x, int y) const
{
    return tiles[x][y].is_mine();
}

bool Board::is_unknown(int x, int y) const
{
    return tiles[x][y].is_unknown();
}

int Board::neighboring_flagged_as(int x, int y, unsigned short flags) const
{
    int flagged = 0;
    for (int nx = x - 1; nx <= x + 1; nx++)
    {
        if (!this->has_tile(nx, 0))
        {
            continue;
        }

        for (int ny = y - 1; ny <= y + 1; ny++)
        {
            if (!this->has_tile(nx, ny) || (ny == y && nx == x))
            {
                continue;
            }
            if (tiles[nx][ny].flags & flags)
            {
                flagged++;
            }
        }
    }
    return flagged;
}

int Board::tile_possibility_score(int x, int y) const
{
    const Tile &tile = tiles[x][y];

    if (tile.is_mine() || tile.is_unknown())
    {
        return std::numeric_limits<int>::max();
    }

    int known_mines = neighboring_flagged_as(x, y, Tile::mine_flag);
    int clue = tile.value - '0';

    if (clue == known_mines)
    {
        return 0;
    }

    int unknown_mines = clue - known_mines;
    int unknowns = neighboring_flagged_as(x, y, Tile::unknown_flag);
    return possibilities[unknowns][unknown_mines];
}

std::vector<Tile *> Board::neighbors_of(const int x, const int y)
{
    std::vector<Tile *> out = std::vector<Tile *>();

    for (int nx = x - 1; nx <= x + 1; nx++)
    {
        if (!has_tile(nx, 0))
        {
            continue;
        }

        for (int ny = y - 1; ny <= y + 1; ny++)
        {
            if (!has_tile(nx, ny) || (ny == y && nx == x))
            {
                continue;
            }

            out.push_back(&(tiles[nx][ny]));
        }
    }

    return out;
}

bool Board::same_size_as(const Board &other) const
{
    return (width() == other.width() && height() == other.height() && mine_count() == other.mine_count());
}

Board Board::join(const Board &a, const Board &b)
{
    if (!a.same_size_as(b))
    {
        throw std::out_of_range("Boards are not the same size");
    }

    Board out = Board(a);

    for (int x = 0; x < out.width(); x++)
    {
        for (int y = 0; y < out.height(); y++)
        {
            out[x][y].flags &= b[x][y].flags;
        }
    }

    return out;
}