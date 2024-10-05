#pragma once

#include "../Tools.hpp"

#include <functional>
#include <iostream>
#include <vector>

using namespace PFT::Tools;

namespace PFT::Methods::Numerical::Pricing
{
    class BinomialTree
    {
    private:
        std::vector<std::vector<double>> underlying_prices;
        std::vector<std::vector<double>> option_prices;

        std::function<double(double)> derivative_function;

    public:
        BinomialTree();
        ~BinomialTree();

        auto compute_underlying_prices() -> void;
        auto compute_option_prices() -> void;

        auto
    };

    class TrinomialTree
    {
        std::vector<std::vector<double>> udnerlying_prices;
        std::vector<std::vector<double>> option_prices;
    };

    class MonteCarlo
    {
    };

    class BlackScholes
    {
    };
}