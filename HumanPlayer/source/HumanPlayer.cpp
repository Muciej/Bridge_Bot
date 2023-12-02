#include <stdexcept>
#include <HumanPlayer/HumanPlayer.hpp>
#include <commands/CommandsUtils.hpp>
#include <commands/CommandCreator.hpp>
#include <utils/CardsUtils.hpp>
#include <utils/Printer.hpp>

void HumanPlayer::gameloop()
{
    std::cout << "Set your name: ";
    std::cin>>client_name;
    client->sendCommand("ADD_PLAYER " + client_name + " PLAYER");

    while(true)
    {
        if(action_needed)
        {
            show_available_commands();
            std::string cmd = choose_and_generate_command();
            client->sendCommand(cmd);
            action_needed = false;
        } else
        {
            server_command = client->popCommandWait();
            std::cout << server_command << std::endl;
            auto type = commands::parseCommand(server_command, command_vector);
            if( type == "SETPOS")
                executeSetPosCommand(command_vector);
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
            else
                unknownCommand(server_command);
        }
    }
}


void HumanPlayer::show_available_commands()
{
    printer::printSortedHand(std::cout, hand);
    std::cout << "Available commands: " << std::endl
              << "1. BID" << std::endl
              << "2. PLAY"<< std::endl;
}

std::string HumanPlayer::choose_and_generate_command()
{
    std::cout << "Choose command to execute: ";
    int cmd_no;
    do
    {
        std::cin >> cmd_no;
        if( cmd_no <0 || cmd_no > 2)
        {
            std::cout << "Invalid command number, try again: ";
        }
    } while (cmd_no > 0 && cmd_no <= 2);

    switch (cmd_no)
    {
    case 1:
        return prepareBidCommand();
    case 2:
        return preparePlayCommand();
    default:
        throw std::runtime_error("Control should not reach here");
    }
}

void HumanPlayer::executeSetPosCommand(const std::vector<std::string>& command_data)
{
    if (command_data[1] != client_name)
    {
        action_needed = false;
        return;
    } else
    {
        position = commands::getPositionFromString(command_data[2]);
        prev_position = utils::getPrevPosition(position);
    }

    std::cout << "Assigned position: " << command_data[2] << std::endl;
}

void HumanPlayer::executeBidderCommand(const std::vector<std::string>& command_data)
{
    std::cout << "Auction has started! First bid will be placed by: " << command_data[1] << std::endl;
    if (commands::getPositionFromString(command_data[1]) == position)
    {
        action_needed = true;
    }
}

void HumanPlayer::executeBidCommand(const std::vector<std::string>& command_data)
{
    std::cout << command_data[1] << " bidded: " << command_data[3] << " " << command_data[2] << std::endl;
    if (commands::getPositionFromString(command_data[1]) == prev_position)
    {
        action_needed = true;
    }
}

void HumanPlayer::executeBidendCommand(const std::vector<std::string>& command_data)
{
    std::cout << "Auction ended! The declarer is " << command_data[1] << " and the contract is: " << command_data[3] << " " << command_data[2];
    dummyPosition = utils::getPartnerPosition(commands::getPositionFromString(command_data[1]));
    if (commands::getPositionFromString(command_data[1]) == position)
    {
        action_needed = true;
    }
}

void HumanPlayer::executePlayCommand(const std::vector<std::string>& command_data)
{
    std::cout << command_data[1] << " played: " << command_data[2] << std::endl;
    if(commands::getPositionFromString(command_data[1]) == dummyPosition)
    {
        utils::drawCardFromHand(dummyHand, commands::getCardFromString(command_data[2]));
        printer::printSortedHand(std::cout, dummyHand);
    }
    if (commands::getPositionFromString(command_data[1]) == prev_position)
    {
        action_needed = true;
    }
}

void HumanPlayer::executeTrickendCommand(const std::vector<std::string>& command_data)
{
    std::cout << command_data[1] << " won the trick!" << std::endl << std::endl;
    if (commands::getPositionFromString(command_data[1]) == position)
    {
        action_needed = true;
    }
}

void HumanPlayer::executeGameendCommand(const std::vector<std::string>& command_data)
{
    std::cout << "Game ended!" << std::endl
              << "winners are: " << command_data[1] << "/" << command_data[2];
}

void HumanPlayer::unknownCommand(const std::string& command)
{
    std::cerr << "Received unknown command from the server: " << command << std::endl;
}

void HumanPlayer::executeDummyHandCommand(const std::vector<std::string>& command_data)
{
    dummyHand = commands::parseHandCommand(command_data, 2);
    printer::printSortedHand(std::cout, dummyHand);
}

std::string HumanPlayer::prepareBidCommand()
{
    std::cout << "1. PASS"
              << "2. NO_TRUMP"
              << "3. SPADES"
              << "4. HEARTS"
              << "5. DIAMONDS"
              << "6. CLUBS"
              << "Choose trump: ";

    int choice;
    std::cin >> choice;

    if(choice == 1)
    {
        return commands_creator.getBidInfoCommand(position, utils::Bid(utils::Trump::PASS, 0));
    } else
    {
        std::cout << "Choose deal (from 1 to 7): ";
        int deal;
        std::cin >> deal;
        utils::Trump trump;
        switch (choice)
        {
        case 2:
            trump = utils::Trump::NO_TRUMP;
            break;
        case 3:
            trump = utils::Trump::SPADES;
            break;
        case 4:
            trump = utils::Trump::HEARTS;
            break;
        case 5:
            trump = utils::Trump::DIAMONDS;
            break;
        case 6:
            trump = utils::Trump::CLUBS;
            break;
        }

        return commands_creator.getBidInfoCommand(position, utils::Bid(trump, deal));
    }
}

std::string HumanPlayer::preparePlayCommand()
{
    for(const auto& card : hand)
    {
        std::cout << card << " ";
    }
    std::cout << std::endl;
    std::cout << "Choose card to play (use first letter of color name instead of symbol), like H10: ";
    std::string card_str;
    std::cin >> card_str;
    char suit_char = card_str[0];
    std::string rank_str = card_str.substr(1);
    int rank;
    if(rank_str == "A")
        rank = utils::RoyalRank::ACE;
    else if(rank_str == "K")
        rank = utils::RoyalRank::KING;
    else if(rank_str == "Q")
        rank = utils::RoyalRank::QUEEN;
    else if(rank_str == "J")
        rank = utils::RoyalRank::JACK;
    else
        rank = std::atoi(rank_str.c_str());

    utils::Suit suit;
    switch (suit_char)
    {
    case 'H':
        suit = utils::Suit::HEARTS;
        break;
    case 'S':
        suit = utils::Suit::SPADES;
        break;
    case 'D':
        suit = utils::Suit::DIAMONDS;
        break;
    case 'C':
        suit = utils::Suit::CLUBS;
    }

    return commands_creator.getPlayCommand(position, utils::Card(rank, suit));
}
