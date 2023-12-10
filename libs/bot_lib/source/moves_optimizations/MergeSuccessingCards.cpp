#include <bot_lib/moves_optimizations/MergeSuccessingCards.hpp>

namespace bot
{
    void MergeSuccessingCards::handle(std::vector<Move>& moves)
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
            present[move.placed_card] = true;
        }
        bool first_in_row = true;
        for(int i = 51; i>=0; i--)
        {
            if (i%13 == 12 || !present[i])
                first_in_row = true;
            if(present[i] && !first_in_row)
            {
                present[i] = false;
            }
        }
        for(const auto& move : moves)
        {
            if(present[move.placed_card])
            {
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
