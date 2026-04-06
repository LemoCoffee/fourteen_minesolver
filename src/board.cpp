#include "board.h"

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

int Board::unknown_neighbors(int x, int y) const
{
    int unknown_count = 0;
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
            if (tiles[nx][ny].is_unknown())
            {
                unknown_count++;
            }
        }
    }
    return unknown_count;
}

int Board::tile_possibility_score(int x, int y)
{
    const Tile &tile = tiles[x][y];

    if (tile.is_mine() || tile.is_unknown())
    {
        return std::numeric_limits<int>::max();
    }

    int clue = tile.value - '0';
    int unknowns = unknown_neighbors(x, y);
    return unknowns - clue;
}