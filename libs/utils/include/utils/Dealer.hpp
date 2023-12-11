#pragma once
#include <vector>
#include <utils/Card.hpp>

namespace utils
{

class Dealer
{
    private:
    std::vector<utils::Card> deck;
    void initializeDeck();

    public:
    Dealer();
    void shuffleDeck();
    std::vector<std::vector<Card>> dealCards();
    void dealCardsIntoIntTable(std::vector<int>& deal, const std::vector<int>& bot_cards);
};

};
