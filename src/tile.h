#ifndef TILE_H
#define TILE_H

struct Tile
{
    char value;
    unsigned short flags;

    static constexpr unsigned short mine_flag = 0b10;
    static constexpr unsigned short unknown_flag = 0b01;

    static const Tile mine;
    static const Tile unknown;
    static const Tile empty;

    Tile(char v) : value(v), flags(0) {}
    Tile(char v, unsigned short f) : value(v), flags(f) {}

    bool operator==(const Tile &rhs) const { return (flags ^ rhs.flags) == 0; }
    bool operator!=(const Tile &rhs) const { return !(*this == rhs); }

    bool is_mine() const { return (flags & mine_flag) != 0; }
    bool is_unknown() const { return (flags & unknown_flag) != 0; }
    bool is_empty() const { return flags == 0 && value == '?'; }
};

#endif