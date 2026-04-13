#include "tile.h"

const Tile Tile::mine = Tile('m', Tile::mine_flag);
const Tile Tile::unknown = Tile(' ', Tile::unknown_flag);
const Tile Tile::empty = Tile('0', 0);
