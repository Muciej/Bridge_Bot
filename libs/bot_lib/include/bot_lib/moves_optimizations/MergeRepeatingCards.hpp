#pragma once
#include <utility>
#include "../moves_optimizations/MoveOptimizer.hpp"

namespace bot
{

class MergeRepeatingCards : public MoveOptimizer
{
    public:
    void handle(std::vector<Move>& moves) override;
};

} // namespace bot
