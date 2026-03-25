#include <vector>
#include "./board.cpp"

std::vector<Board> solve (const Board& puzzle) {

}

bool is_valid_board (const Board& board) {
    for (int x = 0; x < board.width(); x++) {
        for (int y = 0; y < board.height(); y++) {

        }
    }
}

bool is_valid_tile (const int x, const int y, const Board& board) {
    Tile* tile = board[x][y];

    if (tile->is_mine() || tile->is_unknown()) { return true; }

    int mine_count = 0;
    int unknown_count = 0;

    for (int nx = x - 1; nx <= x + 1; nx++) {
        for (int ny = y - 1; y <= y + 1; ny++) {
            if (!board.has_tile(nx, ny) || (ny == y && nx == x)) { continue; }
            if (board[nx][ny]->is_mine()) { mine_count++; }
            if (board[nx][ny]->is_unknown()) { unknown_count++; }
        }

        if (mine_count > (tile->value - '0')) { return false; }
    }

    return (mine_count + unknown_count == (tile->value - '0'));
}