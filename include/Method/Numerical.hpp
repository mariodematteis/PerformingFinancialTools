#pragma once

#include "../Tools.hpp"

#include <functional>
#include <iostream>
#include <vector>

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

        void compute_underlying_prices();
        void compute_option_prices();
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