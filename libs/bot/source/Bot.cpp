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

Bot::Bot(std::string bot_name, ClientPtr client_ptr) : client(std::move(client_ptr))
{
    global_game_state.bot_name = bot_name;
    move_optimize_chain = std::make_unique<MergeSuccessingCards>();
    init_current_state();
}

void Bot::gameloop()
{
    client->sendCommand("ADD_PLAYER " + global_game_state.bot_name + " BOT");
    std::string server_command;
    std::vector<std::string> command_data;
    while(true)
    {
        server_command = client->popCommandWait();
        auto type = commands::parseCommand(server_command, command_data);
        if( type == "SETPOS")
            executeSetPosCommand(command_data);
        else if( type == "HAND")
            executeHandCommand(command_data);
        else if( type == "BIDDER")
            executeBidderCommand(command_data);
        else if( type == "BID")
            executeBidCommand(command_data);
        else if( type == "BIDEND")
            executeBidendCommand(command_data);
        else if( type == "PLAY")
            executePlayCommand(command_data);
        else if( type == "TRICKEND")
            executeTrickendCommand(command_data);
        else if( type == "GAMEEND")
            executeGameendCommand(command_data);
        else if( type == "DUMMY_HAND")
            executeDummyHandCommand(command_data);
    }

}

Card Bot::evaluateNextMove(const GameState& state)
{
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
    return best_card_to_play;
}

int Bot::evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize)
{
    if( depth == 0 || state.game_end )
    {
        return evaluator->evaluate(state);
    }

    auto moves = generateMoves(state);
    generateStatesAfterEachMove(moves);
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

utils::Bid evaluateNextBid(const GameState& state)
{
    return utils::Bid();
}

void Bot::generateStatesAfterEachMove(const std::vector<Move>& moves)
{

}

void Bot::init_current_state()
{
    for(int i = 0; i<=4; i++)
    {
        for(int j = 0; j<52; j++)
        {
            current_state.player_cards_points[i][j] = 0;
        }
    }
}

void Bot::executeSetPosCommand(std::vector<std::string> command_data)
{
    if (command_data[1] != global_game_state.bot_name)
    {
        return;
    } else
    {
        global_game_state.bot_position = commands::getPositionFromString(command_data[2]);
    }
}

void Bot::executeHandCommand(std::vector<std::string> command_data)
{
    // update bot cards
}

void Bot::executeBidderCommand(std::vector<std::string> command_data)
{
    // check if bot is the bidder and place bid if so
}

void Bot::executeBidCommand(std::vector<std::string> command_data)
{
    // adjust card situation according to the placed bid
}

void Bot::executeBidendCommand(std::vector<std::string> command_data)
{
    global_game_state.declarer_pos = commands::getPositionFromString(command_data[1]);
}

void Bot::executePlayCommand(std::vector<std::string> command_data)
{
    // adjust current situation accordingly
    // check if it's bot move now
}

void Bot::executeTrickendCommand(std::vector<std::string> command_data)
{
    // adjust current state
    // check if it's bot move now
}

void Bot::executeGameendCommand(std::vector<std::string> command_data)
{
    // restart bot to initial state
}

void Bot::executeDummyHandCommand(std::vector<std::string> command_data)
{
    // adjust situation by adding dummy's card
}


} // namespace bot
