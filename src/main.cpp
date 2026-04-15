#include "variantBasic.h"
#include <iostream>
#include "utility.h"

int main()
{
    auto solver = VariantBasic();
    auto board = Board(5, 5, 10);
    board[3][0] = Tile('0');
    board[1][3] = Tile('5');
    board[0][4] = Tile('2');
    board[3][4] = Tile('4');

    board[2][0] = Tile('1');
    board[4][0] = Tile::unknown;
    board[2][1] = Tile('3');
    board[3][1] = Tile('1');
    board[4][1] = Tile('1');

    board[2][2] = Tile('4');
    board[4][2] = Tile('2');

    std::cout << "Input:" << std::endl;
    std::cout << board_to_string(board);

    std::cout << "Output:" << std::endl;
    std::cout << board_to_string(solver.solve(board));
    return 0;
}
