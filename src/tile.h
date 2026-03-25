#ifndef TILE_H
#define TILE_H

struct Tile {
    char value;
    unsigned short flags;

    static constexpr unsigned short mine_flag = 0b0000000000000001;
    static constexpr unsigned short unknown_flag = 0b0000000000000010;

    static const Tile Tile::mine;
    static const Tile Tile::unknown;

    Tile(char v) : value(v), flags(0) {}
    Tile(char v, unsigned short f) : value(v), flags(f) {}

    bool is_mine() const { return (flags & mine_flag) != 0; }
    bool is_unknown() const { return (flags & unknown_flag) != 0; }
};

#endif