#include <gtest/gtest.h>
#include "../basic.h"

TEST(BASIC_TILES, FLAG_CHECKS)
{
    Board b = Board(1, 1, 1);

    EXPECT_FALSE(b.is_mine(0, 0));
    EXPECT_TRUE(b.is_unknown(0, 0));

    b[0][0] = Tile('1');
    EXPECT_FALSE(b.is_mine(0, 0));
    EXPECT_FALSE(b.is_unknown(0, 0));

    b[0][0] = Tile::mine;
    EXPECT_TRUE(b.is_mine(0, 0));
    EXPECT_FALSE(b.is_unknown(0, 0));
}

TEST(BASIC_TILES, 2x2_UNKNOWNS_TILE)
{
    Board b = Board(2, 2, 1);

    b[0][0] = Tile('1');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));

    b[1][0] = Tile::mine;
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
}

TEST(BASIC_TILES, BASIC_TILE)
{
    Board b = Board(3, 3, 1);

    b[1][1] = Tile('1');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));

    b[2][1] = Tile::mine;
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
}

TEST(BASIC_TILES, SINGLE_TILE)
{
    Board b = Board(1, 1, 0);

    b[0][0] = Tile('0');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
}

TEST(BASIC_TILES, INSUFFICIENT_MINES)
{
    Board b = Board(2, 2, 1);

    b[0][0] = Tile('4');
    b[1][0] = Tile::unknown;
    b[0][1] = Tile::unknown;
    b[1][1] = Tile::unknown;
    EXPECT_FALSE(is_valid_tile(0, 0, b));
}

TEST(BASIC_TILES, 2X2_1_BOMB)
{
    Board b = Board(2, 2, 1);

    b[0][1] = Tile('1');
    b[1][1] = Tile('1');
    EXPECT_TRUE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
    EXPECT_TRUE(is_valid_tile(0, 1, b));
    EXPECT_TRUE(is_valid_tile(1, 1, b));

    b[0][0] = Tile('1');
    b[1][0] = Tile('0');
    EXPECT_FALSE(is_valid_tile(0, 0, b));
    EXPECT_TRUE(is_valid_tile(1, 0, b));
    EXPECT_FALSE(is_valid_tile(0, 1, b));
    EXPECT_FALSE(is_valid_tile(1, 1, b));
}

TEST(BASIC_TILES, TILE_SCORING)
{
    Board b = Board(3, 3, 1);

    b[1][1] = Tile('1');
    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::unknown_flag), 8);
    EXPECT_EQ(b.tile_possibility_score(1, 1), 8);

    b[2][1] = Tile('1');
    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::unknown_flag), 7);
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::unknown_flag), 4);
    EXPECT_EQ(b.tile_possibility_score(1, 1), 7);
    EXPECT_EQ(b.tile_possibility_score(2, 1), 4);

    b[2][1] = Tile('2');
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::unknown_flag), 4);
    EXPECT_EQ(b.tile_possibility_score(2, 1), 6);

    b[1][0] = Tile::mine;
    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::unknown_flag), 6);
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::unknown_flag), 3);
    EXPECT_EQ(b.tile_possibility_score(1, 1), 0);
    EXPECT_EQ(b.tile_possibility_score(2, 1), 3);
}