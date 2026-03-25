#include <gtest/gtest.h>
#include "../basic.h"

TEST(BASIC_TILES, TILE_VALIDITY) {
    Board b = Board(2, 2, 1);

    b[0][0] = Tile('1');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));

    b[1][0] = Tile::mine;
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));

    b[0][1] = Tile('1');
    b[1][1] = Tile('1');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
    EXPECT_TRUE(is_valid_tile(0, 1, b));
    EXPECT_TRUE(is_valid_tile(1, 1, b));

    b[0][0] = Tile('2');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
    EXPECT_TRUE(is_valid_tile(0, 1, b));
    EXPECT_TRUE(is_valid_tile(1, 1, b));

    b[1][0] = Tile('0');
    EXPECT_FALSE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
    EXPECT_FALSE(is_valid_tile(0, 1, b));
    EXPECT_FALSE(is_valid_tile(1, 1, b));

    b[0][0] = Tile('4');
    b[1][0] = Tile::unknown;
    b[0][1] = Tile::unknown;
    b[1][1] = Tile::unknown;
    EXPECT_FALSE(is_valid_tile(0, 0, b));
}