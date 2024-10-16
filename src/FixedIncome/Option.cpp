#include "Derivative/Option.hpp"

namespace PFT::Security::Derivative
{

    EuropeanCallOption::EuropeanCallOption() {

    }

    EuropeanCallOption::~EuropeanCallOption() {

    }

    void EuropeanCallOption::describe() {

    }

    double EuropeanCallOption::black_scholes_price() const
    {
        return bsm_model.european_call_option_price(
            get_asset_price(),
            get_strike_price(),
            get_interest_rate(),
            get_maturity(),
            0.0,
            get_sigma(),
            0.0);
    };

    double EuropeanCallOption::delta() const {
        return 0.0;
    }

    double EuropeanCallOption::gamma() const {
        return 0.0;
    }

    double EuropeanCallOption::theta() const
    {
        return 0.0;
    }

    double EuropeanCallOption::speed() const
    {
        return 0.0;
    }

    double EuropeanCallOption::charm() const {
        return 0.0;
    }

    double EuropeanCallOption::colour() const
    {
        return 0.0;
    }

    double EuropeanCallOption::vega() const
    {
        return 0.0;
    }

    double EuropeanCallOption::rho() const {
        return 0.0;
    }

    double EuropeanCallOption::vanna() const {
        return 0.0;
    }

    double EuropeanCallOption::volga() const {
        return 0.0;
    }

    EuropeanPutOption::EuropeanPutOption() {

    }

    EuropeanPutOption::~EuropeanPutOption() {

    }

    void EuropeanPutOption::describe() {

    }


    double EuropeanPutOption::black_scholes_price() const
    {
        return bsm_model.european_put_option_price(
            get_asset_price(),
            get_strike_price(),
            get_interest_rate(),
            get_maturity(),
            0.0,
            get_sigma(),
            0.0);
    };

    double EuropeanPutOption::delta() const {
        return 0.0;
    }

    double EuropeanPutOption::gamma() const {
        return 0.0;
    }

    double EuropeanPutOption::theta() const
    {
        return 0.0;
    }

    double EuropeanPutOption::speed() const
    {
        return 0.0;
    }

    double EuropeanPutOption::charm() const {
        return 0.0;
    }

    double EuropeanPutOption::colour() const
    {
        return 0.0;
    }

    double EuropeanPutOption::vega() const
    {
        return 0.0;
    }

    double EuropeanPutOption::rho() const {
        return 0.0;
    }

    double EuropeanPutOption::vanna() const {
        return 0.0;
    }

    double EuropeanPutOption::volga() const {
        return 0.0;
    }
}