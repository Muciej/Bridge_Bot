#include <limits>
#include <vector>
#include <algorithm>
#include <thread>
#include <bot_lib/Bot.hpp>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>
#include <utils/Printer.hpp>

#include <commands/CommandsUtils.hpp>
#include <bot_lib/state_evaluator/BaseEvaluator.hpp>
#include <bot_lib/bid_evaluator/BaseBidEvaluator.hpp>

namespace bot
{

using utils::Card;

Bot::Bot(std::string bot_name, ClientPtr client_ptr) : client(std::move(client_ptr))
{
    global_game_state.bot_name = bot_name;
    state_evaluator = std::make_unique<BaseEvaluator>();
    bid_evaluator = std::make_unique<BaseBidEvaluator>();
}

void Bot::gameloop()
{
    using namespace std::chrono_literals;
    client->sendCommand("ADD_PLAYER " + global_game_state.bot_name + " BOT");
    std::string server_command;
    std::vector<std::string> command_data;
    while(true)
    {
        std::this_thread::sleep_for(300ms);
        server_command = client->popCommandWait();
        std::this_thread::sleep_for(300ms);
        auto type = commands::parseCommand(server_command, command_data);
        if (is_dummy && type != "GAMEEND")
            continue;
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

int getLowestMove(const std::vector<Move>& moves, const GlobalGameState& global_state, const utils::Position& position)
{
    int lowest = 64;
    for(const auto& move : moves)
    {
        if(move.who_placed_card == position && (move.placed_card % 13 < lowest % 13))
            lowest = move.placed_card;
    }
    return lowest;
}

int getLowestSuit(const GameState& state, const utils::Position& position, const utils::Suit& suit)
{
    int suit_int = static_cast<int>(suit);
    int pos_ind = static_cast<int>(position);

    for(int i = 13 * suit_int; i < (13 * suit_int) + 13; i++)
    {
        if( state.player_cards_points[pos_ind][i] > 0 )
            return i;
    }

    return 0;
}

Card Bot::evaluateNextMove(GameState& state)
{
    auto moves = move_generator.generateInitialMovesSet(state, global_game_state);
    int max = std::numeric_limits<int>::min();
    int best_card_to_play;
    utils::Position who_s_card;
    for (const auto& move : moves)
    {
        int eval = evaluateNextMoveDetails(move.state_after, evaluation_depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true);
        if (eval > max)
        {
            best_card_to_play = move.placed_card;
            who_s_card = move.who_placed_card;
        }
    }

    std::cout << "Before checks: " << utils::getCardFromInt(best_card_to_play) << "\t" << who_s_card << std::endl;

    if(who_s_card != global_game_state.bot_position && global_game_state.now_moving == global_game_state.bot_position)
    {
        // best_card_to_play = getLowestMove(moves, global_game_state, global_game_state.bot_position);
        best_card_to_play = getLowestSuit(state, global_game_state.bot_position, utils::getSuitFromIntCard(best_card_to_play));
    } else if (who_s_card == global_game_state.bot_position && global_game_state.declarer_pos == global_game_state.bot_position && global_game_state.now_moving == global_game_state.dummy_position)
    {
        // best_card_to_play = getLowestMove(moves, global_game_state, global_game_state.dummy_position);
        best_card_to_play = getLowestSuit(state, global_game_state.dummy_position, utils::getSuitFromIntCard(best_card_to_play));
    }
    std::cout << "After checks: " << utils::getCardFromInt(best_card_to_play) << "\t" << who_s_card << std::endl << std::endl;
    return utils::getCardFromInt(best_card_to_play);
}

int Bot::evaluateNextMoveDetails(const GameState& state, int depth, int alpha, int beta, bool maximize)
{
    if( depth == 0 || state.game_end )
    {
        return state_evaluator->evaluateState(state, global_game_state);
    }

    auto moves = move_generator.generateMovesSet(state, global_game_state);
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
        for (auto& move : moves)
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

utils::Bid Bot::evaluateNextBid(GameState& state)
{
    auto next_bid = bid_evaluator->evalueNextBid(state, global_game_state);
    return next_bid;
}

void Bot::init_current_state()
{
    for(int i = 0; i<4; i++)
    {
        if(i == static_cast<int>(global_game_state.bot_position))
        {
            resetPoints(current_state, static_cast<utils::Position>(i));
        } else
        {
            for(int j = 0; j<52; j++)
            {
                current_state.player_cards_points[i][j] = REQUIRED_LEGAL_SAMPLES / 4;
            }
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
        global_game_state.bot_partner_posititon = utils::getPartnerPosition(global_game_state.bot_position);
        init_current_state();
    }
}

void Bot::executeHandCommand(std::vector<std::string> command_data)
{
    if (commands::getPositionFromString(command_data[1]) != global_game_state.bot_position)
        return;

    auto hand = commands::parseHandCommand(command_data, 2);
    std::cout << printer::printSortedHand(hand) << std::endl;
    for(const auto& card : hand)
    {
        move_generator.removeCardFromCardPointTables(current_state, utils::getCardAsInt(card));
        current_state.player_cards_points[static_cast<int>(global_game_state.bot_position)][utils::getCardAsInt(card)] = REQUIRED_LEGAL_SAMPLES;
    }
}

void Bot::executeBidderCommand(std::vector<std::string> command_data)
{
    // check if bot is the bidder and place bid if so
    global_game_state.now_moving = commands::getPositionFromString(command_data[1]);
    if(global_game_state.now_moving == global_game_state.bot_position)
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
    if(global_game_state.now_moving == global_game_state.bot_position)
    {
        global_game_state.now_moving = utils::getNextPosition(global_game_state.now_moving);
        return;
    }
    bid_evaluator->updateAfterPlacedBid(current_state, global_game_state);
    global_game_state.now_moving = utils::getNextPosition(global_game_state.now_moving);
    if(global_game_state.now_moving == global_game_state.bot_position && !bot::isBiddingEnded(global_game_state.bidding))
    {
        auto bot_bid = evaluateNextBid(current_state);
        client->sendCommand(command_creator.getBidInfoCommand(global_game_state.bot_position, bot_bid));
    }
}

void Bot::executeBidendCommand(std::vector<std::string> command_data)
{
    global_game_state.declarer_pos = commands::getPositionFromString(command_data[1]);
    global_game_state.dummy_position = utils::getPartnerPosition(global_game_state.declarer_pos);
    global_game_state.now_moving = utils::getNextPosition(global_game_state.declarer_pos);
    global_game_state.contract = commands::parseBidCommand(command_data);
    current_state.current_trick_no = 1;
    current_state.tricker = global_game_state.now_moving;
    if(global_game_state.dummy_position == global_game_state.bot_position)
    {
        is_dummy = true;
        return;
    }
    if( global_game_state.now_moving == global_game_state.bot_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.getPlayCommand(global_game_state.bot_position, card));
    }
}

void Bot::executePlayCommand(std::vector<std::string> command_data)
{
    auto card_played = commands::parsePlayCommand(command_data);
    move_generator.removeCardFromCardPointTables(current_state, utils::getCardAsInt(card_played));
    if(!current_state.in_trick)
    {
        current_state.in_trick = true;
        current_state.trick_suit = card_played.suit;
    }
    global_game_state.now_moving = utils::getNextPosition(global_game_state.now_moving);
    if (global_game_state.now_moving == current_state.tricker)
    {
        return;
    }
    if( global_game_state.now_moving == global_game_state.bot_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.getPlayCommand(global_game_state.bot_position, card));
    } else if( global_game_state.declarer_pos == global_game_state.bot_position && global_game_state.now_moving == global_game_state.dummy_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.clientGetDummyPlayCommand(global_game_state.bot_position, card));
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
    }
    current_state.in_trick = false;
    current_state.current_trick_no++;
    current_state.tricker = trick_winner;
    global_game_state.now_moving = trick_winner;
    if( global_game_state.now_moving == global_game_state.bot_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.getPlayCommand(global_game_state.bot_position, card));
    } else if( global_game_state.declarer_pos == global_game_state.bot_position && global_game_state.now_moving == global_game_state.dummy_position)
    {
        auto card = evaluateNextMove(current_state);
        client->sendCommand(command_creator.clientGetDummyPlayCommand(global_game_state.bot_position, card));
    }
}

void Bot::executeDummyHandCommand(std::vector<std::string> command_data)
{
    // adjust situation by adding dummy's card
    auto dummy_hand = commands::parseHandCommand(command_data, 2);
    resetPoints(current_state, global_game_state.dummy_position);
    for(const auto& card : dummy_hand)
    {
        current_state.player_cards_points[static_cast<int>(global_game_state.dummy_position)][utils::getCardAsInt(card)] = REQUIRED_LEGAL_SAMPLES;
    }
}

void Bot::executeGameendCommand( std::vector<std::string> command_data)
{
    global_game_state = GlobalGameState();
    current_state = GameState();
    is_dummy = false;
    init_current_state();
}

} // namespace bot
