#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "tile.h"

struct Board {
    std::vector<std::vector<Tile>> tiles;

    Board(std::vector<std::vector<Tile>>& t, int mines) : tiles(t), mine_count(mines) {}

    Board(int w, int h, int mines) : mine_count(mines) {
        tiles.resize(w, std::vector<Tile>(h, Tile::unknown));
    }

    std::vector<Tile>& operator [](size_t x) { return tiles[x]; }
    const std::vector<Tile>& operator [](size_t x) const { return tiles[x]; }

    int width() const { return tiles.size(); }
    int height() const { return tiles[0].size(); } // Assume board is always rectangular
    bool has_tile(const int x, const int y) const { return x >= 0 && x < width() && y >= 0 && y < height(); }

    int mine_count;
};

#endif
