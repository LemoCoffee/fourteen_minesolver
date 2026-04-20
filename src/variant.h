#ifndef VARIANT_H
#define VARIANT_H

#include "board.h"

struct SolverInfo {
    size_t evaluations;
};

class IVariant
{
private:
    SolverInfo* statistics = new SolverInfo();
public:
    virtual ~IVariant() = default;

    virtual Board solve(const Board &puzzle);
    virtual std::vector<Board> get_possibilities(const int x, const int y, const Board &board) = 0;
    virtual std::vector<Board> get_possibilities(const Board &board) = 0;

    static Board collapse_possibilities(const std::vector<Board> &possibilities);

    virtual std::vector<Board> global_brute_force(const Board &board);
    virtual std::vector<Board> global_brute_force_helper(Board &board, const std::vector<std::pair<int, int>> &unknowns, int current_pos, int remaining_mines);

    virtual bool is_valid_tile(const int x, const int y, const Board &board) const = 0;
    virtual bool is_valid_board(const Board &board) const = 0;

    void reset_statistics() { delete statistics; statistics = new SolverInfo(); }
    void count_evaluation() const { statistics->evaluations++; }
    const SolverInfo& get_statistics() const { return *statistics;}
};

#endif