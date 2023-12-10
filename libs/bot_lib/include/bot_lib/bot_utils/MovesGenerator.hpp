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
    void addToSuit(const GameState& state, std::vector<Move>& moves, const utils::Position& player);
    void addStrictlyToSuit(const GameState& state, std::vector<Move>& moves, const utils::Position& player, utils::Suit suit);
    void addAllTricker(const GameState& state, std::vector<Move>& moves, bool tricker_suits[4]);

    public:
    MoveGenerator();
    std::unique_ptr<MoveOptimizer> move_optimize_chain;
    std::vector<Move> generateMovesSet(const GameState& current_state, const GlobalGameState& global_state);
    void removeCardFromCardPointTables(GameState& state, int placed_card);
    void updateCurrentStateCards(GameState& state, const GlobalGameState& global_state, int placed_card);
};

} // namespace bot

