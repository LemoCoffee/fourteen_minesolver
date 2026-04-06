#include <vector>
#include "tile.h"
#include <limits>

#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
public:
    std::vector<std::vector<Tile>> tiles;
    int mine_count;

    Board(std::vector<std::vector<Tile>> &t, int mines) : tiles(t), mine_count(mines) {}
    Board(int w, int h, int mines) : mine_count(mines)
    {
        tiles.resize(w, std::vector<Tile>(h, Tile::unknown));
    }

    std::vector<Tile> &operator[](size_t x) { return tiles[x]; }
    const std::vector<Tile> &operator[](size_t x) const { return tiles[x]; }

    int width() const { return tiles.size(); }
    int height() const { return tiles[0].size(); } // Assume board is always rectangular

    bool has_tile(const int x, const int y) const;
    bool is_mine(const int x, const int y) const;
    bool is_unknown(const int x, const int y) const;
    int unknown_neighbors(const int x, const int y) const;
    int tile_possibility_score(int x, int y);
};

#endif
