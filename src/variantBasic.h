#ifndef BASIC_H
#define BASIC_H

#include "variant.h"

struct SolverInfo {
    size_t evaluations;
};

class VariantBasic : public IVariant
{
private:
    Board collapse_possibilities(std::vector<Board> possibilities);

    Board global_brute_force(const Board &board);
    std::vector<Board> global_brute_force_helper(Board &board, const std::vector<std::pair<int, int>> &unknowns, int current_pos, int remaining_mines);

    SolverInfo* statistics = new SolverInfo();
public:

    Board solve(const Board &puzzle) override;
    std::vector<Board> get_possibilites(const int x, const int y, const Board &board) override;

    void reset_statistics() { delete statistics; statistics = new SolverInfo(); }
    void count_evaluation() const { statistics->evaluations++; }
    const SolverInfo& get_statistics() const { return *statistics;}

    bool is_valid_tile(const int x, const int y, const Board &board) const override;
    bool is_valid_board(const Board &board) const override;
};

#endif
