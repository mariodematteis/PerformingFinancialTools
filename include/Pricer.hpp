#pragma once

#include "Derivative/Option.hpp"

namespace PFT::Pricer
{
    class Engine
    {
    private:
        PFT::Methods::Analytical::BlackScholesMerton bsm_model;
        PFT::Methods::Numerical

            public : auto
                     operator()(const PFT::Security::Derivative::Option::EuropeanCallOption &option,
                                double t = 0.0) const -> double
        {
            return bsm_model.european_call_option_price(option.get_asset_price(),
                                                        option.get_strike_price(),
                                                        option.get_interest_rate(),
                                                        option.get_maturity(),
                                                        t,
                                                        option.get_sigma(),
                                                        0.0);
        }

        auto operator()(const PFT::Security::Derivative::Option::EuropeanPutOption &option,
                        double t = 0.0) const -> double
        {
            return bsm_model.european_put_option_price(option.get_asset_price(),
                                                       option.get_strike_price(),
                                                       option.get_interest_rate(),
                                                       option.get_maturity(),
                                                       t,
                                                       option.get_sigma(),
                                                       0.0);
        }

        auto operator()(const co)
    };
}