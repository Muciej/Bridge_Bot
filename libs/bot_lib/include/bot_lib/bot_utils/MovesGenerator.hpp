#pragma once
#include "../moves_optimizations/MoveOptimizer.hpp"
#include "GameState.hpp"
#include "GlobalGameState.hpp"
#include "Move.hpp"

namespace bot
{

class MoveGenerator
{
    public:
    MoveGenerator();
    std::unique_ptr<MoveOptimizer> move_optimize_chain;
    std::vector<Move> generateMovesSet(const GameState& current_state, const GlobalGameState& global_state);
    void updateState(Move& move);
};

} // namespace bot

