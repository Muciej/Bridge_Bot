#pragma once
#include "../moves_optimizations/MoveOptimizer.hpp"
#include "GameState.hpp"
#include "GlobalGameState.hpp"
#include "Move.hpp"

namespace bot
{

class MoveGenerator
{
    private:
    void updateStateAfterMove(Move& move, const GlobalGameState& global_state);

    public:
    MoveGenerator();
    std::unique_ptr<MoveOptimizer> move_optimize_chain;
    std::vector<Move> generateMovesSet(const GameState& current_state, const GlobalGameState& global_state);
    void updateCardPoints(GameState& state, int placed_card, bool check_trick_col = true);
};

} // namespace bot

