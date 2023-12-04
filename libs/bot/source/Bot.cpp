#include <limits>
#include <vector>
#include <algorithm>
#include <bot/Bot.hpp>
#include <utils/Card.hpp>
#include <bot/moves_optimizations/MergeSuccessingCards.hpp>
#include <commands/CommandsUtils.hpp>

namespace bot
{

using utils::Card;

Bot::Bot(ClientPtr client_ptr, std::string bot_name) : client(std::move(client_ptr)), name(bot_name)
{
    move_optimize_chain = std::make_unique<MergeSuccessingCards>();
}

void Bot::gameloop()
{
    GameState state;
    client->sendCommand("ADD_PLAYER " + name + " BOT");
    std::string server_command;
    std::vector<std::string> command_vector;
    while(true)
    {
        server_command = client->popCommandWait();
        auto type = commands::parseCommand(server_command, command_vector);
        if( type == "SETPOS")
            executeSetPosCommand(command_vector);
        else if( type == "HAND")
            executeHandCommand(command_vector);
        else if( type == "BIDDER")
            executeBidderCommand(command_vector);
        else if( type == "BID")
            executeBidCommand(command_vector);
        else if( type == "BIDEND")
            executeBidendCommand(command_vector);
        else if( type == "PLAY")
            executePlayCommand(command_vector);
        else if( type == "TRICKEND")
            executeTrickendCommand(command_vector);
        else if( type == "GAMEEND")
            executeGameendCommand(command_vector);
        else if( type == "DUMMY_HAND")
            executeDummyHandCommand(command_vector);
    }
    
}

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

std::vector<Move> Bot::generateMoves(const GameState& state)
{
    std::vector<Move> moves = generateLegalMoves(state);
    move_optimize_chain->handle(moves);
    return moves;
}

std::vector<Move> Bot::generateLegalMoves(const GameState& state)
{
    std::vector<Move> legal_moves;

    // TODO 

    return legal_moves;
}

void executeSetPosCommand(std::vector<std::string> command_vector)
{

}

void executeHandCommand(std::vector<std::string> command_vector)
{

}

void executeBidderCommand(std::vector<std::string> command_vector)
{

}

void executeBidCommand(std::vector<std::string> command_vector)
{

}

void executeBidendCommand(std::vector<std::string> command_vector)
{

}

void executePlayCommand(std::vector<std::string> command_vector)
{

}

void executeTrickendCommand(std::vector<std::string> command_vector)
{

}

void executeGameendCommand(std::vector<std::string> command_vector)
{

}

void executeDummyHandCommand(std::vector<std::string> command_vector)
{

}


} // namespace bot
