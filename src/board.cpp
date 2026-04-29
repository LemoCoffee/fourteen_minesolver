#include "board.h"
#include <stdexcept>
#include <limits>

bool Board::operator==(const Board &rhs) const
{
    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {
            if (tiles[x][y] != rhs[x][y])
            {
                return false;
            }
        }
    }

    return true;
}

int Board::flagged_count(unsigned short flags) const
{
    int count = 0;
    for (int x = 0; x < width(); x++)
    {
        for (int y = 0; y < height(); y++)
        {
            if (tiles[x][y].flags & flags)
            {
                count++;
            }
        }
    }
    return count;
}

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

int Board::neighboring_mines(const int x, const int y) const
{
    return (tiles[x][y].value - '0');
}

int Board::neighboring_flagged_as(int x, int y, unsigned short flags) const
{
    int flagged = 0;
    for (auto p : neighbors(x, y)) {
        if (p->flags & flags)
        {
            flagged++;
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

std::vector<Tile *> Board::neighbors(const int x, const int y)
{
    std::vector<Tile *> out;

    for (auto p : neighbor_coords(x, y)) {
        out.emplace_back(&(tiles[p.first][p.second]));
    }

    return out;
}

std::vector<const Tile *> Board::neighbors(const int x, const int y) const
{
    std::vector<const Tile *> out;

    for (auto p : neighbor_coords(x, y)) {
        out.emplace_back(&(tiles[p.first][p.second]));
    }

    return out;
}

std::vector<Tile *> Board::orthogonal(const int x, const int y) {
    std::vector<Tile *> out;

    for (auto p : orthogonal_coords(x, y)) {
        out.emplace_back(&(tiles[p.first][p.second]));
    }

    return out;
}

std::vector<std::pair<int, int>> Board::orthogonal_coords(const int x, const int y) const {
    std::vector<std::pair<int, int>> out;

    if (has_tile(x - 1, y)) {
        out.emplace_back(x - 1, y);
    }

    if (has_tile(x, y - 1)) {
        out.emplace_back(x, y - 1);
    }

    if (has_tile(x + 1, y)) {
        out.emplace_back(x + 1, y);
    }

    if (has_tile(x, y + 1)) {
        out.emplace_back(x, y + 1);
    }

    return out;
}

std::vector<std::pair<int, int>> Board::neighbor_coords(const int x, const int y) const
{
    std::vector<std::pair<int, int>> out = {};

    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (has_tile(i, j) && !(i == x && j == y))
            {
                out.emplace_back(i, j);
            }
        }
    }

    return out;
}

std::vector<std::pair<int, int>> Board::flagged_coords(const unsigned short flags) const
{
    std::vector<std::pair<int, int>> out = {};

    for (int i = 0; i < width(); i++)
    {
        for (int j = 0; j < height(); j++)
        {
            if (has_tile(i, j) && (tiles[i][j].flags == flags))
            {
                out.emplace_back(i, j);
            }
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
            if (out[x][y] != b[x][y])
            {
                out[x][y] = Tile::unknown;
            }
        }
    }

    return out;
}