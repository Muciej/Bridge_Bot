#pragma once
#include <vector>
#include <utils/Player.hpp>
#include <utils/Bid.hpp>
namespace bot
{

/// @brief Class used to store data about game state
/// it stores data that is constant during whole game
struct GlobalGameState
{
    std::string bot_name;
    utils::Position bot_position;
    utils::Position declarer_pos;
    utils::Position dummy_position;
    utils::Position bot_partner_posititon;
    utils::Bid contract;
    std::vector<utils::Bid> bidding;
    utils::Position now_moving;
};

} // namespace bot
