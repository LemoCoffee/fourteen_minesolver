#include <vector>
#include "tile.h"
#include <limits>

#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
    inline static const std::vector<std::vector<int>> possibilities = {
        {1, -1, -1, -1, -1, -1, -1, -1, -1}, // 0
        {1, 1, -1, -1, -1, -1, -1, -1, -1},  //
        {1, 2, 1, -1, -1, -1, -1, -1, -1},   //
        {1, 3, 3, 1, -1, -1, -1, -1, -1},    //
        {1, 4, 6, 4, 1, -1, -1, -1, -1},     // 4
        {1, 5, 10, 10, 5, 1, -1, -1, -1},    //
        {1, 6, 15, 20, 15, 6, 1, -1, -1},    //
        {1, 7, 21, 35, 35, 21, 7, 1, -1},    //
        {1, 8, 28, 56, 70, 56, 28, 8, 1},    // 8
    };

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

    std::vector<Tile *> neighbors_of(const int x, const int y);

    bool has_tile(const int x, const int y) const;
    bool is_mine(const int x, const int y) const;
    bool is_unknown(const int x, const int y) const;
    int neighboring_flagged_as(const int x, const int y, unsigned short flags) const;
    int tile_possibility_score(int x, int y) const;
};

#endif
