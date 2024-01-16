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

    /// @brief Updates game state after given move
    /// @param move - contains state to be updated and played card
    /// @param global_state - global game state
    void updateStateAfterMove(Move& move, const GlobalGameState& global_state);

    /// @brief Adds moves compliant with suit of current trick
    /// that can also mean all player cards if he does not have any cards in required suit
    void addToSuit(const GameState& state, std::vector<Move>& moves, const utils::Position& player);

    /// @brief Adds moves compliant with suit of current trick
    /// ignores situation when player does not have cards in required suit
    void addStrictlyToSuit(const GameState& state, std::vector<Move>& moves, const utils::Position& player, utils::Suit suit);

    /// @brief Adds all moves for all tricker cards and checks what suit does tricker have.
    /// @param state - current game state
    /// @param moves - vector to which moves will be added
    /// @param tricker_suits - array that will be usedd to save suits possessed by tricker
    void addAllTricker(const GameState& state, std::vector<Move>& moves, bool tricker_suits[4]);

    // std::vector<Move> generateMovesTwo(const GameState& current_state, const GlobalGameState& global_state);
    std::vector<Move> generateMovesThree(const GameState& current_state, const GlobalGameState& global_state);
    std::vector<Move> generateMovesFour(const GameState& current_state, const GlobalGameState& global_state);

    public:
    MoveGenerator();
    std::unique_ptr<MoveOptimizer> move_optimize_chain;

    /// @brief Generates legal moves set based on game state
    /// @return vector of moves that can be made by pair that is currently moving
    std::vector<Move> generateMovesSet(const GameState& current_state, const GlobalGameState& global_state);
    std::vector<Move> generateInitialMovesSet(const GameState& current_state, const GlobalGameState& global_state);
    void removeCardFromCardPointTables(GameState& state, int placed_card);
    void updateCurrentStateCards(GameState& state, const GlobalGameState& global_state, int placed_card);
    int getTurnNumber(const GameState& state, const utils::Position& moving);
};

} // namespace bot

