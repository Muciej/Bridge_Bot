#include <bot_lib/moves_optimizations/MergeRepeatingCards.hpp>

namespace bot
{
    void MergeRepeatingCards::handle(std::vector<Move>& moves)
    {
        std::vector<Move> cleared_moves;
        cleared_moves.reserve(moves.size());
        bool present[52];
        for(int i = 0; i<52; i++)
        {
            present[i] = false;
        }
        for(const auto& move : moves)
        {
            if(!present[move.placed_card])
            {
                present[move.placed_card] = true;
                cleared_moves.push_back(move);
            }
        }
        moves = cleared_moves;
        if(next != nullptr)
        {
            next->handle(moves);
        }
    }
} // namespace bot