#pragma once
#include <vector>
#include <memory>
#include "../bot_utils/Move.hpp"

namespace bot
{
    class MoveOptimizer
    {
        protected:
        std::unique_ptr<MoveOptimizer> next = nullptr;
        public:
        void setNext(std::unique_ptr<MoveOptimizer> next_ptr)
        {
            next = std::move(next_ptr);
        }
        virtual void handle(std::vector<Move>& moves) = 0;
    };
} // namespace bot



