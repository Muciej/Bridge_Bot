#include <limits>
#include <vector>
#include <algorithm>
#include <bot/Bot.hpp>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>
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

utils::Bid Bot::evaluateNextBid(const GameState& state)
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
        resetPoints(static_cast<utils::Position>(i));
    }
}

void Bot::updateCurrentStateAfterBid()
{
    // recalculate points
}

void Bot::updateStateAfterMove(GameState& state, const utils::Card& played_card, const utils::Position& played_position)
{
    // adjust point in each player table
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
    if (commands::getPositionFromString(command_data[1]) != global_game_state.bot_position)
        return;

    auto hand = commands::parseHandCommand(command_data, 2);
    for(const auto& card : hand)
    {
        current_state.player_cards_points[static_cast<int>(global_game_state.bot_position)][utils::getCardAsInt(card)]++;
        current_state.player_cards_points_sum[global_game_state.bot_position]++;
    }
}

void Bot::executeBidderCommand(std::vector<std::string> command_data)
{
    // check if bot is the bidder and place bid if so
    now_moving = commands::getPositionFromString(command_data[1]);
    if(now_moving == global_game_state.bot_position)
    {
        auto bid = evaluateNextBid(current_state);
        client->sendCommand(command_creator.getBidInfoCommand(global_game_state.bot_position, bid));
    }
}

void Bot::executeBidCommand(std::vector<std::string> command_data)
{
    // adjust card situation according to the placed bid
    auto bid = commands::parseBidCommand(command_data);
    global_game_state.bidding.push_back(bid);
    updateCurrentStateAfterBid();
    now_moving = utils::getNextPosition(now_moving);
    if(now_moving == global_game_state.bot_position)
    {
        auto bot_bid = evaluateNextBid(current_state);
        client->sendCommand(command_creator.getBidInfoCommand(global_game_state.bot_position, bot_bid));
    }
}

void Bot::executeBidendCommand(std::vector<std::string> command_data)
{
    global_game_state.declarer_pos = commands::getPositionFromString(command_data[1]);
    global_game_state.dummy_position = utils::getPartnerPosition(global_game_state.declarer_pos);
    now_moving = global_game_state.declarer_pos;
    global_game_state.contract = commands::parseBidCommand(command_data);
    if( now_moving == global_game_state.bot_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.getPlayCommand(global_game_state.bot_position, card));
    }
}

void Bot::executePlayCommand(std::vector<std::string> command_data)
{
    // adjust current situation accordingly
    // check if it's bot move now
    auto card_played = commands::parsePlayCommand(command_data);
    updateStateAfterMove(current_state, card_played, now_moving);
    now_moving = utils::getNextPosition(now_moving);
    if( now_moving == global_game_state.bot_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.getPlayCommand(global_game_state.bot_position, card));
    }
}

void Bot::executeTrickendCommand(std::vector<std::string> command_data)
{
    // adjust current state
    // check if it's bot move now
    auto trick_winner = commands::getPositionFromString(command_data[1]);
    if (trick_winner == global_game_state.bot_position || trick_winner == utils::getPartnerPosition(global_game_state.bot_position))
    {
        current_state.pair_tricks_won++;
        current_state.in_trick = false;
        current_state.current_trick_no++;
    }
    now_moving = trick_winner;
    if( now_moving == global_game_state.bot_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.getPlayCommand(global_game_state.bot_position, card));
    }
}

void Bot::executeDummyHandCommand(std::vector<std::string> command_data)
{
    // adjust situation by adding dummy's card
    auto dummy_hand = commands::parseHandCommand(command_data, 2);
    resetPoints(global_game_state.dummy_position);
    for(const auto& card : dummy_hand)
    {
        current_state.player_cards_points[static_cast<int>(global_game_state.dummy_position)][utils::getCardAsInt(card)]++;
        current_state.player_cards_points_sum[static_cast<int>(global_game_state.dummy_position)]++;
    }
}

void Bot::executeGameendCommand(std::vector<std::string> command_data)
{
    global_game_state = GlobalGameState();
    current_state = GameState();
    init_current_state();
}

void Bot::resetPoints(utils::Position position)
{
    for(int i = 0; i<13; i++)
    {
        current_state.player_cards_points[static_cast<int>(position)][i] = 0;
    }
    current_state.player_cards_points_sum[static_cast<int>(position)] = 0;
}


} // namespace bot
