#pragma once
#include <vector>
#include <utils/Card.hpp>

namespace utils
{

class Dealer
{
    private:
    std::vector<utils::Card> deck;


    /// @brief Initializes deck of cards
    void initializeDeck();

    public:
    Dealer();

    /// @brief Reshuffles deck
    void shuffleDeck();

    /// @brief Deals cards present in deck into vectors for each player
    /// @return - vector of players hands (each of them is also a vector)
    std::vector<std::vector<Card>> dealCards();


    /// @brief For bot use. Fills deal vector with cards that currently are in the deck
    /// omitting cards present in bot_cards vector
    /// @param deal - vector to draw cards into
    /// @param bot_cards - vector of bot cards
    void dealCardsIntoIntTable(std::vector<int>& deal, const std::vector<int>& bot_cards);
};

};
