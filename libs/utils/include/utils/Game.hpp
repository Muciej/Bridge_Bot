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
    END,
};

struct Game
{
    GameState state = GameState::IN_LOBBY;
    Position declarer = Position::NORTH;
    Position now_moving = Position::NORTH;
    Bid contract = Bid(Trump::PASS, 0);
    Trick tricks[13];
    int current_trick = 0;
    int dealer_won_tricks = 0;
    bool dummy_card_revealed = false;

    Trick getCurentTrick();
    int getScore();
    std::pair<Position, Position> getWinners();
};

};
