#ifndef BOARD_H
#define BOARD_H

#include <limits>
#include <vector>
#include "tile.h"

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

    int _mine_count;

public:
    std::vector<std::vector<Tile>> tiles;

    Board(std::vector<std::vector<Tile>> &t, int mines) : _mine_count(mines), tiles(t) {}
    Board(int w, int h, int mines) : _mine_count(mines)
    {
        tiles.resize(w, std::vector<Tile>(h, Tile::unknown));
    }

    Board(const Board &other)
    {
        tiles = std::vector<std::vector<Tile>>(other.tiles);
        _mine_count = other.mine_count();
    }

    Board &operator=(const Board &other)
    {
        if (this != &other)
        {
            tiles = std::vector<std::vector<Tile>>(other.tiles);
            _mine_count = other.mine_count();
        }
        return *this;
    }

    std::vector<Tile> &operator[](size_t x) { return tiles[x]; }
    const std::vector<Tile> &operator[](size_t x) const { return tiles[x]; }

    std::vector<Tile> &operator&=(size_t x) { return tiles[x]; }

    int width() const { return tiles.size(); }
    int height() const { return tiles[0].size(); } // Assume board is always rectangular
    int mine_count() const { return _mine_count; }

    std::vector<const Tile *> neighbors_of(const int x, const int y) const;
    std::vector<Tile *> neighbors_of(const int x, const int y);

    bool has_tile(const int x, const int y) const;
    bool is_mine(const int x, const int y) const;
    bool is_unknown(const int x, const int y) const;
    int neighboring_mines(const int x, const int y) const;
    int neighboring_flagged_as(const int x, const int y, unsigned short flags) const;
    int tile_possibility_score(int x, int y) const;

    bool same_size_as(const Board &other) const;

    static Board join(const Board &a, const Board &b);
};

#endif
