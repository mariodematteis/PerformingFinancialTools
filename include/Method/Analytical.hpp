#pragma once

#include "Tools.hpp"

#include <iostream>

namespace PFT::Methods::Analytical
{
    class BlackScholesMerton
    {
    private:
        PFT::Tools::standardize_moneyness _d1;
        PFT::Tools::critical_value _d2;

        PFT::Tools::norm_cdf cdf;

    public:
        auto european_call_option_price(double underlying_price,
                                        double strike_price,
                                        double interest_rate,
                                        double maturity,
                                        double current_time,
                                        double sigma,
                                        double dividend_yield) const -> double
        {
            auto d1 = _d1(underlying_price,
                          strike_price,
                          interest_rate,
                          maturity,
                          current_time,
                          sigma,
                          dividend_yield);

            auto d2 = _d2(underlying_price,
                          strike_price,
                          interest_rate,
                          maturity,
                          current_time,
                          sigma,
                          dividend_yield);

            return underlying_price * cdf(d1) - strike_price * std::exp(-interest_rate * (maturity - current_time)) * cdf(d2);
        }

        auto european_put_option_price(double underlying_price,
                                       double strike_price,
                                       double interest_rate,
                                       double maturity,
                                       double current_time,
                                       double sigma,
                                       double dividend_yield) const -> double
        {

            auto d1 = _d1(underlying_price,
                          strike_price,
                          interest_rate,
                          maturity,
                          current_time,
                          sigma,
                          dividend_yield);

            auto d2 = _d2(underlying_price,
                          strike_price,
                          interest_rate,
                          maturity,
                          current_time,
                          sigma,
                          dividend_yield);
            return strike_price * std::exp(-interest_rate * (maturity - current_time)) * cdf(-d2) * underlying_price * cdf(-d1);
        }
    };

    class Black
    {
    };

    class Heston
    {
    };

    class HullWhite
    {
    };

}
