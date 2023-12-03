#include <sstream>
#include <commands/CommandCreator.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>

namespace commands
{

    string getPositionString(const utils::Position& position)
    {
        switch (position)
        {
        case utils::Position::NORTH :
            return "NORTH";
        case utils::Position::EAST :
            return "EAST";
        case utils::Position::SOUTH :
            return "SOUTH";
        case utils::Position::WEST :
            return "WEST";
        }
        return "NORTH";
    }

    string getTrumpString(const utils::Trump& trump)
    {
        switch (trump)
        {
        case utils::Trump::CLUBS :
            return "CLUBS";
        case utils::Trump::DIAMONDS :
            return "DIAMONDS";
        case utils::Trump::HEARTS :
            return "HEARTS";
        case utils::Trump::SPADES :
            return "SPADES";
        case utils::Trump::PASS :
            return "PASS";
        case utils::Trump::NO_TRUMP :
            return "NO_TRUMP";
        }
        return "PASS";
    }

    /// @brief Returns command that sets position of player with given name
    /// @param name - name of the player
    /// @param position - player position at the table
    /// @return prepared command
    /// Format: SETPOS [ name ] [ position ]
    string CommandCreator::serverGetSetPositionCommand(const string& name, const utils::Position& position)
    {
        return "SETPOS " + name + " " + getPositionString(position);
    }

    /// @brief Returns command containing info about given player cards
    /// @param position - position of a player
    /// @param hand - cards that were given to player at given postiion
    /// @return prepared command
    /// Format: HAND [ position ] [ rank|color ]x13
    /// where rank can be from {2,3,4,5,6,7,8,9,10,J,Q,K,A}
    /// and color can be from {♠, ♥, ♦, ♣}
    string CommandCreator::serverGetCardsInfoCommand(const utils::Position& position, std::vector<utils::Card>& hand)
    {
        std::stringstream ss;
        for(const auto& card : hand)
        {
            ss << " " << card;
        }
        return "HAND " + getPositionString(position) + ss.str();
    }

    /// @brief Returns command that provides information about position of player, who won bidding
    /// @param dealer_position - position, on which player who won bidding is
    /// @return prepared command
    /// Format: BIDDER [ position ]
    string CommandCreator::serverGetStartBiddingCommand(const utils::Position& dealer_position)
    {
        return "BIDDER " + getPositionString(dealer_position);
    }

    /// @brief Returns command that informs aobut bid placed by player
    /// for client, the command should also be indication that bid was accepted
    /// shared between server and clients
    /// @param position - position of bidding player
    /// @param bid - placed bid
    /// @return prepared command
    /// Format: BID [ position ] [ proposed trump ] [ amount ]
    string CommandCreator::getBidInfoCommand(const utils::Position& position, const utils::Bid& bid)
    {
        return "BID " + getPositionString(position) + " " + getTrumpString(bid.trump) + " " + std::to_string(bid.deal);
    }

    /// @brief Returns command signalling the end of bidding along with declarer and game deal
    /// @param position - position of the declarer
    /// @param deal - game deal
    /// @return prepared command
    /// Format: BIDEND [ position ] [ deal ]
    string CommandCreator::serverGetBidEndCommand(const utils::Position& position, const utils::Bid& bid)
    {
        return "BIDEND " + getPositionString(position) + " " + getTrumpString(bid.trump) + " " + std::to_string(bid.deal);
    }

    /// @brief Returns command informing about player move
    /// shared between server and clients
    /// @param position - position of player who has just moved
    /// @param played_card - card played by that player
    /// @return prepared command
    /// Format: PLAY [ position ] [ played card ]
    string CommandCreator::getPlayCommand(const utils::Position& position, const utils::Card& played_card)
    {
        std::stringstream ss;
        ss << played_card;
        return "PLAY " + getPositionString(position) + " " + ss.str();
    }

    /// @brief Returns command that informs about end of the game and it's result
    /// @param winner_1
    /// @param winner_2
    /// @param points_won
    /// @return prepared command
    /// Format: GAMEEND [ position 1 ] [ position 2 ] [ points won ]
    string CommandCreator::serverGetGameEndCommand(const utils::Position& winner_1, const utils::Position& winner_2, int points_won)
    {
        return "GAMEEND " + getPositionString(winner_1) + " " + getPositionString(winner_2) + " " + std::to_string(points_won);
    }

    /// @brief Returns command with error message for all players
    /// @param msg - error message
    /// @return prepared command
    /// Format: ERROR ALL [ message ]
    string CommandCreator::serverGetErrorMsgAllCommand(const string& msg)
    {
        return "ERROR ALL " + msg;
    }

    /// @brief Returns command with error message for given player
    /// @param position - position of player who should receive command
    /// @param msg - error message
    /// @return prepared command
    /// Format: ERROR [ position ] [ error message ]
    string CommandCreator::serverGetErrorMsgCommand(const utils::Position& position, const string& msg)
    {
        return "ERROR " + getPositionString(position) + " " + msg;
    }

    /// @brief Returns command informing about winner of trick
    /// @param winner
    /// @return prepared command
    /// Format: TRICKEND [ position ]
    string CommandCreator::serverGetTrickResultCommand(const utils::Position& winner)
    {
        return "TRICKEND " + getPositionString(winner);
    }

    /// @brief Returns command with request to add a new player to a game
    /// @param name - name of player to be added
    /// @param isBot - information if the player is bot
    /// @return - prepared command
    /// FORMAT: ADD_PLAYER [ name ] [ BOT/PLAYER ]
    string CommandCreator::clientGetPlayerAddCommand(const string name, bool isBot)
    {
        return "ADD_PLAYER " + name + (isBot ? " BOT" : " PLAYER");
    }

    /// @brief Returns command informing about dummy's hand
    /// @param dummy_position - position of dummy
    /// @param hand - dummy's hand
    /// @return - prepared command
    /// FORMAT: DUMMY_HAND [ position ] [ position ] [ rank|color ]x13
    /// where rank can be from {2,3,4,5,6,7,8,9,10,J,Q,K,A}
    /// and color can be from {♠, ♥, ♦, ♣}
    string CommandCreator::serverGetDummyCardInfoCommand(const utils::Position& dummy_position, std::vector<utils::Card>& hand)
    {
        std::stringstream ss;
        for(const auto& card : hand)
        {
            ss << " " << card;
        }
        return "DUMMY_HAND " + getPositionString(dummy_position) + ss.str();
    }

    string CommandCreator::clientGetDummyPlayCommand(const utils::Position& position, const utils::Card played_card)
    {
        std::stringstream ss;
        ss << played_card;
        return "DUMMY_PLAY " + getPositionString(position) + " " + ss.str();
    }
};
