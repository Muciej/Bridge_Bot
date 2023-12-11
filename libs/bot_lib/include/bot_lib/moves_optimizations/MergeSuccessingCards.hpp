#pragma once
#include <utility>
#include "../moves_optimizations/MoveOptimizer.hpp"

namespace bot
{

class MergeSuccessingCards : public MoveOptimizer
{
    public:
    void handle(std::vector<Move>& moves) override;
};

} // namespace bot


