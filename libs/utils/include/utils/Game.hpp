#pragma once
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>

namespace utils
{

enum class GameState
{
    IN_LOBBY,
    BIDDING,
    PLAYING,
};

struct Game
{
    GameState state = GameState::IN_LOBBY;
    utils::Position declarer = utils::Position::NORTH;
    utils::Position now_moving = utils::Position::NORTH;
    utils::Bid contract;
    //Trick tricks[13];
};

};
