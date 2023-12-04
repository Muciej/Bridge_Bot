#include <bot/Bot.hpp>
#include <utils/Card.hpp>
#include <limits>
#include <vector>
#include <algorithm>

namespace bot
{

using utils::Card;

Card Bot::evaluateNextMove(const GameState& state)
{
//     start measuring
    auto moves = generateMoves(state);
    int max = std::numeric_limits<int>::max();
    Card best_card_to_play;
    for (const auto& move : moves)
    {
        int eval = evaluateNextMoveDetails(move.state_after, evaluation_depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true);
        if (eval < max)
        {
            best_card_to_play = move.placed_card;
        }
    }
//     stop measuring
//     add measure to history
    return best_card_to_play;
}

int Bot::evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize)
{
    if( depth == 0 || state.game_end )
    {
        return evaluator->evaluate(state);
    } 

    auto moves = generateMoves(state);
    int eval;

    if ( maximize )
    {
        int maxEval = std::numeric_limits<int>::min();
        for (const auto& move : moves)
        {
            eval = evaluateNextMoveDetails(move.state_after, depth-1, alpha, beta, false);
            maxEval = std::max(eval, maxEval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
            {
                break;
            }
        }
        return maxEval;
    } else
    {
        int minEval = std::numeric_limits<int>::max();
        for (const auto& move : moves)
        {
            eval = evaluateNextMoveDetails(move.state_after, depth-1, alpha, beta, move.state_after.maximize);
            minEval = std::min(eval, minEval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }

        return minEval;
    }
}

std::vector<Move> generateMoves(const State& state)
{
    std::vector<Move> moves;
//     generateLegalMoves
//     launch_optimization_chain
    return moves;
}

void generateLegalMoves()
{
    
}

}
