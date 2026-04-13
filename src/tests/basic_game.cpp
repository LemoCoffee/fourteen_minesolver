#include <gtest/gtest.h>
#include "../variantBasic.h"

static VariantBasic basic = VariantBasic();

TEST(BOARD_METHODS, ACCESSING)
{
    Board b = Board(3, 3, 3);
    b[1][1] = Tile('1');

    EXPECT_EQ(b[1][1], Tile('1'));
}

TEST(BOARD_METHODS, NEIGHBORING_MINES)
{
    Board b = Board(3, 3, 3);
    b[1][1] = Tile('1');

    EXPECT_EQ(b.neighboring_mines(1, 1), 1);
}

TEST(BOARD_METHODS, NEIGHBORING_COORDINATES)
{
    Board b = Board(3, 3, 3);

    std::vector<std::pair<int, int>> CENTER = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
    EXPECT_EQ(b.coordinate_neighbors_of(1, 1), CENTER);

    std::vector<std::pair<int, int>> EDGE = {{0, 0}, {0, 2}, {1, 0}, {1, 1}, {1, 2}};
    EXPECT_EQ(b.coordinate_neighbors_of(0, 1), EDGE);

    std::vector<std::pair<int, int>> CORNER = {{0, 1}, {1, 0}, {1, 1}};
    EXPECT_EQ(b.coordinate_neighbors_of(0, 0), CORNER);
}

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
    EXPECT_TRUE(basic.is_valid_tile(0, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 0, b));

    b[1][0] = Tile::mine;
    EXPECT_TRUE(basic.is_valid_tile(0, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 0, b));
}

TEST(BASIC_TILES, BASIC_TILE)
{
    Board b = Board(3, 3, 1);

    b[1][1] = Tile('1');
    EXPECT_TRUE(basic.is_valid_tile(0, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 0, b));

    b[2][1] = Tile::mine;
    EXPECT_TRUE(basic.is_valid_tile(0, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 0, b));
}

TEST(BASIC_TILES, SINGLE_TILE)
{
    Board b = Board(1, 1, 0);

    b[0][0] = Tile('0');
    EXPECT_TRUE(basic.is_valid_tile(0, 0, b));
}

TEST(BASIC_TILES, INSUFFICIENT_MINES)
{
    Board b = Board(2, 2, 1);

    b[0][0] = Tile('4');
    b[1][0] = Tile::unknown;
    b[0][1] = Tile::unknown;
    b[1][1] = Tile::unknown;
    EXPECT_FALSE(basic.is_valid_tile(0, 0, b));
}

TEST(BASIC_TILES, 2X2_1_BOMB)
{
    Board b = Board(2, 2, 1);

    b[0][1] = Tile('1');
    b[1][1] = Tile('1');
    EXPECT_TRUE(basic.is_valid_tile(0, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(0, 1, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 1, b));

    b[0][0] = Tile('1');
    b[1][0] = Tile('0');
    EXPECT_FALSE(basic.is_valid_tile(0, 0, b));
    EXPECT_TRUE(basic.is_valid_tile(1, 0, b));
    EXPECT_FALSE(basic.is_valid_tile(0, 1, b));
    EXPECT_FALSE(basic.is_valid_tile(1, 1, b));
}

TEST(BASIC_TILES, NEIGHBOR_FLAG_COMPARISON)
{
    Board b = Board(3, 3, 1);

    b[1][1] = Tile('1');
    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::unknown_flag), 8);

    b[2][1] = Tile('1');
    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::unknown_flag), 7);
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::unknown_flag), 4);

    b[2][1] = Tile('2');
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::unknown_flag), 4);

    b[1][0] = Tile::mine;
    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::unknown_flag), 6);
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::unknown_flag), 3);

    EXPECT_EQ(b.neighboring_flagged_as(1, 1, Tile::mine_flag), 1);
    EXPECT_EQ(b.neighboring_flagged_as(2, 1, Tile::mine_flag), 1);
}

TEST(BASIC_TILES, TILE_SCORING)
{
    Board b = Board(3, 3, 1);

    b[1][1] = Tile('1');
    EXPECT_EQ(b.tile_possibility_score(1, 1), 8);

    b[2][1] = Tile('1');
    EXPECT_EQ(b.tile_possibility_score(1, 1), 7);
    EXPECT_EQ(b.tile_possibility_score(2, 1), 4);

    b[2][1] = Tile('2');
    EXPECT_EQ(b.tile_possibility_score(2, 1), 6);

    b[1][0] = Tile::mine;
    EXPECT_EQ(b.tile_possibility_score(1, 1), 0);
    EXPECT_EQ(b.tile_possibility_score(2, 1), 3);
}

TEST(BASIC_TILES, CORNER_TILE_SCORING)
{
    Board b = Board(2, 2, 1);

    b[1][1] = Tile('1');
    EXPECT_EQ(b.tile_possibility_score(1, 1), 3);

    b[0][1] = Tile('1');
    EXPECT_EQ(b.tile_possibility_score(1, 1), 2);
    EXPECT_EQ(b.tile_possibility_score(0, 1), 2);

    b[0][1] = Tile('2');
    EXPECT_EQ(b.tile_possibility_score(0, 1), 1);

    b[1][0] = Tile::mine;
    EXPECT_EQ(b.tile_possibility_score(1, 1), 0);
    EXPECT_EQ(b.tile_possibility_score(0, 1), 1);
}

TEST(BOARD_EXPLORE, BOARD_JOINING)
{
    Board a = Board(1, 1, 1);
    Board b = Board(1, 1, 1);

    a[0][0] = Tile::mine;
    b[0][0] = Tile::mine;

    Board joined_board = Board::join(a, b);

    EXPECT_TRUE(joined_board[0][0].flags == Tile::mine.flags);
    EXPECT_FALSE(joined_board[0][0].flags == Tile::unknown.flags);
}

TEST(BOARD_EXPLORE, TILE_PERMUTATIONS)
{
    Board board = Board(3, 1, 1);

    board[1][0] = Tile('1');

    Board EXPECTED_PERMUTATION_A = Board(board);
    EXPECTED_PERMUTATION_A[0][0] = Tile::mine;
    EXPECTED_PERMUTATION_A[2][0] = Tile::empty;
    Board EXPECTED_PERMUTATION_B = Board(board);
    EXPECTED_PERMUTATION_B[0][0] = Tile::empty;
    EXPECTED_PERMUTATION_B[2][0] = Tile::mine;
    std::vector<Board> EXPECTED_PERMUTATIONS = {EXPECTED_PERMUTATION_A, EXPECTED_PERMUTATION_B};

    bool FOUND_A = false;
    bool FOUND_B = false;

    auto possibilities = basic.get_possibilites(1, 0, board);
    for (Board &b : possibilities)
    {
        if (b == EXPECTED_PERMUTATION_A)
        {
            FOUND_A = true;
        }

        if (b == EXPECTED_PERMUTATION_B)
        {
            FOUND_B = true;
        }
    }

    EXPECT_TRUE(FOUND_A);
    EXPECT_TRUE(FOUND_B);
}

TEST(BASIC_GAME, SINGLE_TILE)
{
    Board b = Board(2, 1, 1);
    b[0][0] = Tile('1');
    Board solved = Board(b);
    b[0][1] = Tile::mine;

    EXPECT_EQ(basic.solve(b), solved);
}

TEST(BASIC_GAME, IMPLICATION)
{
    Board b = Board(3, 2, 2);
    b[0][0] = Tile('1');
    b[1][0] = Tile('2');
    b[2][0] = Tile::empty;
    Board solved = Board(b);
    b[2][1] = Tile::mine;

    EXPECT_EQ(basic.solve(b), solved);
}