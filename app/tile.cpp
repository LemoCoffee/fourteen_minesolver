struct Tile {
    char value;
    unsigned short flags; // Flags as in properties not "flagged mine"

    Tile(char v) : value(v), flags(0) {}
    Tile(char v, unsigned short f) : value(v), flags(f) {}

    bool is_mine() { return flags & mine_flag != 0; }
    bool is_unknown() { return flags & unknown_flag != 0; }

    const unsigned short mine_flag =    0b0000000000000001;
    const unsigned short unknown_flag = 0b0000000000000010;
};