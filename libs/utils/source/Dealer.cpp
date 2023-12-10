#include <utils/Dealer.hpp>
#include <utils/Card.hpp>
#include <utils/CardsUtils.hpp>
#include <algorithm>
#include <ctime>
#include <vector>

namespace utils
{

Dealer::Dealer()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    initializeDeck();
    shuffleDeck();
}

void Dealer::initializeDeck()
{
    for (int suit = static_cast<int>(Suit::CLUBS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        for (int rank = 2; rank <= static_cast<int>(utils::ACE); ++rank) {
            deck.emplace_back(Card{static_cast<char>(rank), static_cast<Suit>(suit)});
        }
    }
}

void Dealer::shuffleDeck()
{
    std::random_shuffle(deck.begin(), deck.end());
}

std::vector<std::vector<Card>> Dealer::dealCards()
{
    std::vector<std::vector<Card>> hands(4);
    for (int i = 0; i < 13; ++i) {
        hands[0].push_back(deck[i]);
        hands[1].push_back(deck[i+13]);
        hands[2].push_back(deck[i+26]);
        hands[3].push_back(deck[i+39]);
    }
    return hands;
}

void Dealer::dealCardsIntoIntTable(std::vector<int>& deal)
{
    for(const auto& card : deck)
    {
        deal.push_back(utils::getCardAsInt(card));
    }
}

};
