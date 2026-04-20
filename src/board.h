#ifndef BOARD_H
#define BOARD_H

#include <limits>
#include <vector>
#include <utility>
#include <stdexcept>
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

    Board(const Board &) = default;
    Board &operator=(const Board &) = default;

    Tile &at(size_t x, size_t y)
    {
        if (x < width() && y < height())
        {
            return tiles[x][y];
        }
        else
        {
            throw std::out_of_range("index out of bounds");
        }
    }

    std::vector<Tile> &operator[](size_t x) { return tiles.at(x); }
    const std::vector<Tile> &operator[](size_t x) const { return tiles.at(x); }

    Tile &operator[](std::pair<int, int> pos) { return tiles.at(pos.first).at(pos.second); }
    const Tile &operator[](std::pair<int, int> pos) const { return tiles.at(pos.first).at(pos.second); }

    bool operator==(const Board &rhs) const;
    bool operator!=(const Board &rhs) const { return !(*this == rhs); }

    int width() const { return tiles.size(); }
    int height() const { return tiles.empty() ? 0 : tiles[0].size(); } // Assume board is always rectangular
    int mine_count() const { return _mine_count; }

    std::vector<const Tile *> neighbors(const int x, const int y) const;
    std::vector<Tile *> neighbors(const int x, const int y);

    std::vector<const Tile *> orthogonal(const int x, const int y) const;
    std::vector<Tile *> orthogonal(const int x, const int y);
    std::vector<std::pair<int, int>> orthogonal_coords(const int x, const int y);

    std::vector<std::pair<int, int>> neighbor_coords(const int x, const int y) const;
    std::vector<std::pair<int, int>> flagged_coords(const unsigned short flags) const;

    int flagged_count(unsigned short flags) const;
    
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
