#pragma once
#include <utils/Player.hpp>
#include <utils/Bid.hpp>

namespace bot
{

struct GlobalGameState
{
    std::string bot_name;
    utils::Position bot_position;
    utils::Position declarer_pos;
    utils::Bid contract;
};

} // namespace bot
