#include <string>
#include "variant.h"

std::string board_to_string(const Board &board)
{
    std::string output = "";

    for (int y = 0; y < board.height(); y++)
    {
        for (int x = 0; x < board.width(); x++)
        {
            output += board[x][y].value;
        }
        output += "\n";
    }

    return output;
}