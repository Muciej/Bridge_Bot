#include <bot_lib/bot_utils/MovesGenerator.hpp>
#include <bot_lib/moves_optimizations/MergeSuccessingCards.hpp>

namespace bot
{

MoveGenerator::MoveGenerator()
{
    move_optimize_chain = std::make_unique<MergeSuccessingCards>();
}

std::vector<Move> MoveGenerator::generateMovesSet(const GameState& current_state, const GlobalGameState& global_state)
{
    // zrboić listę dostępnych ruchów dla tego, KTO TERAZ SIĘ RUSZA. Nie dla bota kurde.
    // oczywiście w ujęciu pary
    std::vector<Move> moves;
    return moves;
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