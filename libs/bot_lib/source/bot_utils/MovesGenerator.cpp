#include <bot_lib/bot_utils/MovesGenerator.hpp>
#include <bot_lib/moves_optimizations/MergeSuccessingCards.hpp>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>
#include <iostream>

namespace bot
{

void clearAllInSuit(int card_points[52], utils::Suit suit)
{
    auto suit_int = static_cast<int>(suit);
    for(int i = (13 * suit_int); i < (13 * suit_int) + 13; i++)
    {
        card_points[i] = 0;
    }
}

MoveGenerator::MoveGenerator()
{
    move_optimize_chain = std::make_unique<MergeSuccessingCards>();
}

void MoveGenerator::addToSuit(const GameState& state, std::vector<Move>& moves, const utils::Position& player)
{
    auto suit_int = static_cast<int>(state.trick_suit);
    auto player_int = static_cast<int>(player);
    bool has_in_suit = false;
    for(int i = suit_int * 13; i < (suit_int * 13) + 13; i++)
    {
        if (state.player_cards_points[player_int][i] != 0)
        {
            moves.push_back(Move(i, player, state));
            has_in_suit = true;
        }
    }
    if(!has_in_suit) // player doesn't have trick suit, so he can play any other card
    {
        for(int i = 0; i<52; i++)
        {
            if (state.player_cards_points[player][i] != 0)
            {
                moves.push_back(Move(i, player, state));
            }
        }
    }
}

void MoveGenerator::addStrictlyToSuit(const GameState& state, std::vector<Move>& moves, const utils::Position& player, utils::Suit suit)
{
    auto suit_int = static_cast<int>(suit);
    auto player_int = static_cast<int>(player);
    for(int i = suit_int * 13; i < (suit_int * 13) + 13; i++)
    {
        if (state.player_cards_points[player_int][i] != 0)
        {
            moves.push_back(Move(i, player, state));
        }
    }
}

void MoveGenerator::addAllTricker(const GameState& state, std::vector<Move>& moves, bool tricker_suits[4])
{
    for(int i = 0; i<52; i++)
    {
        if (state.player_cards_points[state.tricker][i] != 0)
        {
            moves.push_back(Move(i, state.tricker, state));
            tricker_suits[i/13] = true;
        }
    }
}

void debugPrintMoveSet(const std::vector<Move>& moves)
{
    std::cout << std::endl;
    for(const auto& move : moves)
    {
        std::cout << move.placed_card << "\t" << move.who_placed_card << std::endl;
    }
}

std::vector<Move> MoveGenerator::generateMovesSet(const GameState& current_state, const GlobalGameState& global_state)
{
    std::vector<Move> moves;

    if(current_state.in_trick)
    {
        // we have to play to trick suit
        auto moving_pair = utils::getEnemiesPositions(current_state.tricker);
        addToSuit(current_state, moves, moving_pair.first);
        addToSuit(current_state, moves, moving_pair.second);
    } else
    {
        // we can set trick suit
        bool tricker_suits[4]{false, false, false, false};
        addAllTricker(current_state, moves, tricker_suits);
        if(tricker_suits[0]) addStrictlyToSuit(current_state, moves, utils::getPartnerPosition(current_state.tricker), static_cast<utils::Suit>(0));
        if(tricker_suits[1]) addStrictlyToSuit(current_state, moves, utils::getPartnerPosition(current_state.tricker), static_cast<utils::Suit>(1));
        if(tricker_suits[2]) addStrictlyToSuit(current_state, moves, utils::getPartnerPosition(current_state.tricker), static_cast<utils::Suit>(2));
        if(tricker_suits[3]) addStrictlyToSuit(current_state, moves, utils::getPartnerPosition(current_state.tricker), static_cast<utils::Suit>(3));
    }

    move_optimize_chain->handle(moves);
    for(auto& move : moves)
    {
        updateStateAfterMove(move, global_state);
    }

    return moves;
}

bool isNewCardHigher(int high_card, int card_placed, utils::Trump trump)
{
    if(card_placed / 13 == high_card / 13)  // same suit
    {
        return high_card > card_placed;
    } else
    {
        if(card_placed / 13 == static_cast<int>(trump))
            return true;
        else
            return false;
    }
}

void MoveGenerator::updateStateAfterMove(Move& move, const GlobalGameState& global_state)
{
    removeCardFromCardPointTables(move.state_after,  move.placed_card);
    if(move.state_after.in_trick)
    {
        bool tricker_pair_won = isNewCardHigher(move.state_after.high_card, move.placed_card, global_state.contract.trump);
        bool bot_pair_tricker = move.state_after.tricker == global_state.bot_position || move.state_after.tricker == global_state.bot_partner_posititon;
        bool bot_pair_won = tricker_pair_won == bot_pair_tricker;
        move.state_after.current_trick_no++;
        move.state_after.game_end = move.state_after.current_trick_no == 13;
        move.state_after.in_trick = false;
        move.state_after.maximize = bot_pair_won;
        move.state_after.pair_tricks_won += bot_pair_won ? 1 : 0;
        move.state_after.tricker = tricker_pair_won ? move.state_after.placed_high_card : move.who_placed_card;
    } else
    {
        // trick start
        move.state_after.high_card = move.placed_card;
        move.state_after.placed_high_card = move.who_placed_card;
        move.state_after.trick_suit = utils::getSuitFromIntCard(move.placed_card);
        move.state_after.in_trick = true;
        move.state_after.maximize = move.state_after.tricker != global_state.bot_position && move.state_after.tricker != global_state.bot_partner_posititon;
    }
}

void MoveGenerator::removeCardFromCardPointTables(GameState& state, int placed_card)
{
    for(int i = 0; i<4 ; i++)
    {
        state.player_cards_points[i][placed_card] = 0;
    }
}

void MoveGenerator::updateCurrentStateCards(GameState& state, const GlobalGameState& global_state, int placed_card)
{
    removeCardFromCardPointTables(state, placed_card);
    if(state.in_trick && state.trick_suit != utils::getSuitFromIntCard(placed_card))   // player does not have trick suit at all
    {
        int trick_col = placed_card / 13;
        for(int i = trick_col * 13; i< (trick_col * 13) + 13; i++)
        {
            state.player_cards_points[static_cast<int>(global_state.now_moving)][i] = 0;
        }
    }
}

} // namespace bot
