#include <vector>
#include "./tile.cpp"

struct Board {
    std::vector<std::vector<Tile*>> tiles;

    std::vector<Tile*>& operator [](size_t x) { return tiles[x]; }
    std::vector<Tile*> operator [](size_t x) const { return tiles[x]; }

    int width() const { return tiles.size(); }
    int height() const { return tiles[0].size(); } // Assume board is always rectangular
    bool has_tile(const int x, const int y) const { return x > 0 && x < width() && y > 0 && y < height(); }

    int mine_count;
};