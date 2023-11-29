#pragma once
#include <string>
#include <vector>
#include <memory>
#include <connection/TcpClient.hpp>
#include <utils/Player.hpp>
#include <utils/Card.hpp>
#include <commands/CommandCreator.hpp>

using ClientPtr = std::unique_ptr<connection::TcpClient>;

class HumanPlayer
{
    public:
    ClientPtr client;
    commands::CommandCreator commands_creator;

    std::string client_name;
    bool action_needed = false;
    utils::Position position;
    std::string server_command;
    std::vector<std::string> command_vector;
    std::vector<utils::Card> hand;

    HumanPlayer(ClientPtr c) : client(std::move(c)) {};

    void show_available_commands();
    std::string choose_and_generate_command();
    std::string prepareBidCommand();
    std::string preparePlayCommand();
    void executeSetPosCommand(std::vector<std::string> command_data);
    void executeBidderCommand(std::vector<std::string> command_data);
    void executeBidCommand(std::vector<std::string> command_data);
    void executeBidendCommand(std::vector<std::string> command_data);
    void executePlayCommand(std::vector<std::string> command_data);
    void executeTrickendCommand(std::vector<std::string> command_data);
    void executeGameendCommand(std::vector<std::string> command_data);
    void executeDummyHandCommand(std::vector<std::string> command_data);
    void unknownCommand(std::vector<std::string> command_data);

    void gameloop();
};
