#include <stdexcept>
#include <HumanPlayer/HumanPlayer.hpp>
#include <commands/CommandsUtils.hpp>
#include <commands/CommandCreator.hpp>
#include <utils/CardsUtils.hpp>
#include <utils/Printer.hpp>
#include <thread>

void HumanPlayer::gameloop()
{
    std::cout << "Set your name: ";
    std::cin>>client_name;
    client->sendCommand("ADD_PLAYER " + client_name + " PLAYER");

    std::thread send_thr( [this] {this->sendThread();});

    while(true)
    {
        server_command = client->popCommandWait();
        // std::cout << server_command << std::endl;
        history.push_back(server_command);
        auto type = commands::parseCommand(server_command, command_vector);
        if( type == "SETPOS")
            executeSetPosCommand(command_vector);
        else if( type == "HAND")
            executeHandCommand(command_vector);
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

        printUI();
    }

    send_thr.join();
}

void HumanPlayer::show_available_commands()
{
    // std::cout << printer::printSortedHand(hand);
    std::cout << std::endl;
    std::cout << "Available commands: " << std::endl
              << "1. BID" << std::endl
              << "2. PLAY"<< std::endl
              << "3. DUMMY_PLAY" << std::endl;
}

std::string HumanPlayer::choose_and_generate_command()
{
    std::cout << "Choose command to execute: ";
    int cmd_no;
    do
    {
        std::cin >> cmd_no;
        if( cmd_no <0 || cmd_no > 3)
        {
            std::cout << "Invalid command number, try again: ";
        }
    } while (cmd_no < 0 || cmd_no > 3);

    switch (cmd_no)
    {
    case 1:
        return prepareBidCommand();
    case 2:
        return preparePlayCommand();
    case 3:
        return prapareDummyPlayCommand();
    default:
        throw std::runtime_error("Control should not reach here");
    }
}

void HumanPlayer::executeSetPosCommand(const std::vector<std::string>& command_data)
{
    if (command_data[1] != client_name)
    {
        return;
    } else
    {
        position = commands::getPositionFromString(command_data[2]);
        prev_position = utils::getPrevPosition(position);
    }

    // std::cout << "Assigned position: " << command_data[2] << std::endl;
    history.push_back("Assigned position: " + command_data[2]);
}

void HumanPlayer::executeBidderCommand(const std::vector<std::string>& command_data)
{
    // std::cout << "Auction has started! First bid will be placed by: " << command_data[1] << std::endl;
    history.push_back("Auction has started! First bid will be placed by: " + command_data[1]);
}

void HumanPlayer::executeBidCommand(const std::vector<std::string>& command_data)
{
    // std::cout << command_data[1] << " bidded: " << command_data[3] << " " << command_data[2] << std::endl;
    history.push_back(command_data[1] + " bidded: " + command_data[3] + " " + command_data[2]);
}

void HumanPlayer::executeBidendCommand(const std::vector<std::string>& command_data)
{
    // std::cout << "Auction ended! The declarer is " << command_data[1] << " and the contract is: "
    //           << command_data[3] << " " << command_data[2] << std::endl;
    history.push_back("Auction ended! The declarer is " + command_data[1] + " and the contract is: "
                                                        + command_data[3] + " " + command_data[2]);
    auto declarer = commands::getPositionFromString(command_data[1]);
    dummyPosition = utils::getPartnerPosition(declarer);
}

void HumanPlayer::executePlayCommand(const std::vector<std::string>& command_data)
{
    // std::cout << command_data[1] << " played: " << command_data[2] << std::endl;
    history.push_back(command_data[1] + " played: " + command_data[2]);
    if(commands::getPositionFromString(command_data[1]) == position)
    {
        utils::drawCardFromHand(hand.value(), commands::getCardFromString(command_data[2]));
    }
    if(commands::getPositionFromString(command_data[1]) == dummyPosition)
    {
        utils::drawCardFromHand(dummyHand.value(), commands::getCardFromString(command_data[2]));
    }
}

void HumanPlayer::executeTrickendCommand(const std::vector<std::string>& command_data)
{
    // std::cout << command_data[1] << " won the trick!" << std::endl << std::endl;
    history.push_back(command_data[1] + " won the trick!\n");
}

void HumanPlayer::executeGameendCommand(const std::vector<std::string>& command_data)
{
    // std::cout << "Game ended!" << std::endl
    //           << "winners are: " << command_data[1] << "/" << command_data[2];
    std::string command = std::string("Game ended! ") + "Winners are: " + command_data[1] + "/" + command_data[2] + "\n";
    history.push_back(command);
}

void HumanPlayer::executeDummyHandCommand(const std::vector<std::string>& command_data)
{
    dummyHand = commands::parseHandCommand(command_data, 2);
}

void HumanPlayer::executeHandCommand(const std::vector<std::string>& command_data)
{
    if (commands::getPositionFromString(command_data[1]) != position)
        return;

    hand = commands::parseHandCommand(command_data, 2);
}

void HumanPlayer::unknownCommand(const std::string& command)
{
    // std::cerr << "Received unknown command from the server: " << command << std::endl;
    history.push_back(std::string("Received unknown command from the server: ") + command);
}

utils::Card getCardFromCin()
{
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

    return utils::Card(rank, suit);
}

std::string HumanPlayer::prepareBidCommand()
{
    std::cout << "1. PASS" << std::endl
              << "2. NO_TRUMP" << std::endl
              << "3. SPADES" << std::endl
              << "4. HEARTS" << std::endl
              << "5. DIAMONDS" << std::endl
              << "6. CLUBS" << std::endl
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
    std::cout << "Choose card to play (use first letter of color name instead of symbol), like H10: ";
    auto card = getCardFromCin();

    return commands_creator.getPlayCommand(position, card);
}

std::string HumanPlayer::prapareDummyPlayCommand()
{
    std::cout << "Choose card to play (use first letter of color name instead of symbol), like H10: ";
    auto card = getCardFromCin();
    return commands_creator.clientGetDummyPlayCommand(position, card);
}

void HumanPlayer::sendThread()
{
    while(true)
    {
        std::string cmd = choose_and_generate_command();
        client->sendCommand(cmd);
        printUI();
    }
}

void HumanPlayer::printUI()
{
    std::cout << std::endl;
    for (const auto& command : history)
    {
        std::cout << command << std::endl;
    }
    std::cout << std::endl << std::endl;

    if(dummyHand)
        std::cout << "Dummy: " << printer::printSortedHand(dummyHand.value()) << std::endl;
    if(hand)
        std::cout << "Your hand: " << printer::printSortedHand(hand.value()) << std::endl;

    show_available_commands();
}