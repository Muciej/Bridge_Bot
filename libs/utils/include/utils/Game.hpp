#pragma once
#include <utils/Bid.hpp>
#include <utils/Card.hpp>
#include <utils/Player.hpp>
#include <utils/Trick.hpp>

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
    Position declarer = Position::NORTH;
    Position now_moving = Position::NORTH;
    Bid contract;
    Trick tricks[13];
    int current_trick = 0;
    Trick getCurentTrick();
};

};
