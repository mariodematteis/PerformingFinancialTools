#include "Derivative/Option.hpp"

namespace PFT::Security::Derivative::Option
{

    double EuropeanCallOption::price() const override
    {
        Engine engine;
        return engine(*this);
    };

    double EuropeanPutOption::price() const override
    {
        Engine engine;
        return engine(*this);
    };

    Engine::operator()(const EuropeanCallOption & option,
                       double t) const->double
    {
        return bsm_model.european_call_option_price(option.get_asset_price(),
                                                    option.get_strike_price(),
                                                    option.get_interest_rate(),
                                                    option.get_maturity(),
                                                    t,
                                                    option.get_sigma(),
                                                    0.0);
    }

    auto Engine::operator()(const EuropeanPutOption &option,
                            double t) const -> double
    {
        return bsm_model.european_put_option_price(option.get_asset_price(),
                                                   option.get_strike_price(),
                                                   option.get_interest_rate(),
                                                   option.get_maturity(),
                                                   t,
                                                   option.get_sigma(),
                                                   0.0);
    }
}