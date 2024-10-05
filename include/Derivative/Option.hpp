#pragma once

#include "Derivative.hpp"
#include "Method/AnalyticalMethod.hpp"

namespace PFT::Security::Derivative
{
    class Option : public Derivative
    {
    private:
        double strike_price = 0.0;
        double interest_rate = 0.0;

        double sigma = 0.0;

    public:
        auto get_strike_price() const -> double { return strike_price; }
        auto get_interest_rate() const -> double { return interest_rate; }
        auto get_sigma() const -> double { return sigma; }

        virtual auto price() const -> double = 0;

        virtual auto delta() const -> double = 0;
        virtual auto gamma() const -> double = 0;
        virtual auto theta() const -> double = 0;
        virtual auto speed() const -> double = 0;
        virtual auto charm() const -> double = 0;
        virtual auto colour() const -> double = 0;
        virtual auto vega() const -> double = 0;
        virtual auto rho() const -> double = 0;
        virtual auto vanna() const -> double = 0;
        virtual auto volga() const -> double = 0;
    };

    class EuropeanOption : virtual public Option
    {
    public:
        using Option::Option;
    };

    class AmericanOption : virtual public Option
    {
    public:
        using Option::Option;
    };

    class CallOption : virtual public Option
    {
    public:
        using Option::Option;
    };

    class PutOption : virtual public Option
    {
    public:
        using Option::Option;
    };

    class EuropeanCallOption : public EuropeanOption, public CallOption
    {
    public:
        using EuropeanOption::EuropeanOption;
        EuropeanCallOption()
        {
        }
        double price() const override;
    };

    class EuropeanPutOption : public EuropeanOption, public PutOption
    {
    public:
        using EuropeanOption::EuropeanOption;
        EuropeanPutOption()
        {
        }
        double price() const override;
    };

}
