#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
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
    utils::Position position;
    utils::Position prev_position;
    std::string server_command;
    std::vector<std::string> command_vector;
    utils::Position dummyPosition;
    std::optional<std::vector<utils::Card>> hand;
    std::optional<std::vector<utils::Card>> dummyHand;
    std::vector<std::string> history;

    HumanPlayer(ClientPtr c) : client(std::move(c)) {};

    void show_available_commands();
    std::string choose_and_generate_command();
    std::string prepareBidCommand();
    std::string preparePlayCommand();
    std::string prapareDummyPlayCommand();
    void executeSetPosCommand(const std::vector<std::string>& command_data);
    void executeHandCommand(const std::vector<std::string>& command_data);
    void executeBidderCommand(const std::vector<std::string>& command_data);
    void executeBidCommand(const std::vector<std::string>& command_data);
    void executeBidendCommand(const std::vector<std::string>& command_data);
    void executePlayCommand(const std::vector<std::string>& command_data);
    void executeTrickendCommand(const std::vector<std::string>& command_data);
    void executeGameendCommand(const std::vector<std::string>& command_data);
    void executeDummyHandCommand(const std::vector<std::string>& command_data);
    void executeErrorCommand(const std::vector<std::string>& command_data);
    void unknownCommand(const std::string& command);
    void sendThread();
    void printUI();

    void gameloop();
};
