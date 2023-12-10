#include <bot_lib/bot_utils/MovesGenerator.hpp>
#include <bot_lib/moves_optimizations/MergeSuccessingCards.hpp>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>

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

std::vector<Move> MoveGenerator::generateMovesSet(const GameState& current_state, const GlobalGameState& global_state)
{
    // zrboić listę dostępnych ruchów dla tego, KTO TERAZ SIĘ RUSZA. Nie dla bota kurde.
    // oczywiście w ujęciu pary
    // pamiętać, żeby stan move.state_after był skopiowany !!!
    std::vector<Move> moves;



    return moves;
}

void MoveGenerator::updateStateAfterMove(Move& move, const GlobalGameState& global_state)
{
    updateCardPoints(move.state_after, move.placed_card, false);
    bool bot_pair_move = (move.player_placed == global_state.bot_position || move.player_placed == global_state.bot_partner_posititon);
    if(move.state_after.in_trick)
    {

    } else
    {
        // trick start
        move.state_after.high_card = move.placed_card;
        move.state_after.trick_suit = utils::getSuitFromIntCard(move.placed_card);
        move.state_after.in_trick = true;
        move.state_after.maximize = !bot_pair_move;
    }
}

void MoveGenerator::updateCardPoints(GameState& state, int placed_card, bool check_trick_col)
{
    for(int i = 0; i<4 ; i++)
    {
        state.player_cards_points[i][placed_card] = 0;
    }
    if( check_trick_col && state.in_trick && state.trick_suit != utils::getSuitFromIntCard(placed_card))   // player does not have trick colour
    {
        int trick_col = placed_card / 13;
        for(int i = trick_col * 13; i< (trick_col * 13) + 13; i++)
        {
            state.player_cards_points[static_cast<int>(state.now_moving)][i] = 0;
        }
    }
}

} // namespace bot

///////////////////////////////////////////////////////////////////////////////////////////////////
// do wywalenia
// std::vector<Move> Bot::generateMoves(const GameState& state)
// {
//     std::vector<Move> moves = generateLegalMoves(state);
//     move_optimize_chain->handle(moves);
//     return moves;
// }

// std::vector<Move> Bot::generateLegalMoves(const GameState& state)
// {
//     return state.in_trick ? generateLegalMovesTrickContinue(state) : generateLegalMovesTrickStart(state);
// }

// std::vector<Move> Bot::generateLegalMovesTrickContinue(const GameState& state)
// {
//     std::vector<Move> moves;
//     char first_suit_index = static_cast<char>(state.card_played_by_opponents.suit) * 13;
//     for(char i = first_suit_index; i<first_suit_index + 13; i++)
//     {
//         if( state.player_cards_points[static_cast<int>(global_game_state.bot_position)][i] > 0 ||
//             state.player_cards_points[static_cast<int>(global_game_state.bot_partner_posititon)][i] > 0)
//         {
//             moves.push_back(Move(i));
//         }
//     }

//     if(moves.size() == 0)   // our pair does not have cards in this suit, so all others are allowed
//     {
//         for(int i = 0; i<52; i++)
//         {
//             if( state.player_cards_points[static_cast<int>(global_game_state.bot_position)][i] > 0 ||
//             state.player_cards_points[static_cast<int>(global_game_state.bot_partner_posititon)][i] > 0)
//             {
//                 moves.push_back(Move(i));
//             }
//         }
//     }
//     return moves;
// }

// std::vector<Move> Bot::generateLegalMovesTrickStart(const GameState& state)
// {
//     std::vector<Move> moves;
//     bool possessed_colors[] = {false, false, false, false};
//     for(int i = 0; i<52; i++)
//     {
//         if( state.player_cards_points[static_cast<int>(global_game_state.bot_position)][i] > 0)
//         {
//             moves.push_back(Move(i));
//             possessed_colors[i/13] = true;
//         }
//     }
//     for(int j = 0; j<4; j++)
//     {
//         if(possessed_colors[j])
//         {
//             int start = 13 * j;
//             for(int i = start; i< start + 13; i++)
//             {
//                 if( state.player_cards_points[static_cast<int>(global_game_state.bot_partner_posititon)][i] > 0)
//                 {
//                     moves.push_back(Move(i));
//                 }
//             }
//         }
//     }
//     return moves;
// }

// void Bot::updateStateAfterMove(GameState& state, int played_card, const utils::Position& played_position)
// {
//     // adjust point in each player table
//     for(int i = 0; i<4; i++)
//     {
//         current_state.player_cards_points[i][played_card] = 0;
//     }
//     if(state.in_trick && )
// }

// void Bot::generateStatesAfterEachMove(const std::vector<Move>& moves)
// {
//     for(auto move : moves)
//     {
//         updateStateAfterMove(move.state_after, move.placed_card, );
//     }
// }