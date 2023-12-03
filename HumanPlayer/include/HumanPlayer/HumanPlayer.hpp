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
    utils::Position prev_position;
    std::string server_command;
    std::vector<std::string> command_vector;
    std::vector<utils::Card> hand;
    utils::Position dummyPosition;
    std::vector<utils::Card> dummyHand;

    HumanPlayer(ClientPtr c) : client(std::move(c)) {};

    void show_available_commands();
    std::string choose_and_generate_command();
    std::string prepareBidCommand();
    std::string preparePlayCommand();
    void executeSetPosCommand(const std::vector<std::string>& command_data);
    void executeHandCommand(const std::vector<std::string>& command_data);
    void executeBidderCommand(const std::vector<std::string>& command_data);
    void executeBidCommand(const std::vector<std::string>& command_data);
    void executeBidendCommand(const std::vector<std::string>& command_data);
    void executePlayCommand(const std::vector<std::string>& command_data);
    void executeTrickendCommand(const std::vector<std::string>& command_data);
    void executeGameendCommand(const std::vector<std::string>& command_data);
    void executeDummyHandCommand(const std::vector<std::string>& command_data);
    void unknownCommand(const std::string& command);
    void sendThread();

    void gameloop();
};
