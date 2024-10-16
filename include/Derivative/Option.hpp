#pragma once

#include "Derivative.hpp"
#include "Method/Analytical.hpp"

#include <format>

namespace PFT::Security::Derivative
{

    static const std::string european_call_option_default_class = "european_call_option";
    static const std::string european_put_option_default_class = "european_put_option";

    static const std::string_view option_description = "";

    class Option : public Derivative
    {
    private:
        double strike_price = 0.0;
        double interest_rate = 0.0;

        double sigma = 0.0;

    protected:
        PFT::Methods::Analytical::BlackScholesMerton bsm_model;

    public:
        double get_strike_price() const { return strike_price; }
        double get_interest_rate() const { return interest_rate; }
        double get_sigma() const { return sigma; }

        virtual double delta() const = 0;
        virtual double gamma() const = 0;
        virtual double theta() const = 0;
        virtual double speed() const = 0;
        virtual double charm() const = 0;
        virtual double colour() const = 0;
        virtual double vega() const = 0;
        virtual double rho() const = 0;
        virtual double vanna() const = 0;
        virtual double volga() const = 0;
    };

    class EuropeanOption : virtual public Option
    {
    };

    class AmericanOption : virtual public Option
    {
    };

    class CallOption : virtual public Option
    {
    };

    class PutOption : virtual public Option
    {
    };

    class EuropeanCallOption : public EuropeanOption, public CallOption
    {
    public:
        EuropeanCallOption();
        ~EuropeanCallOption();
        void describe() override;
        double black_scholes_price() const;

        double delta() const override;
        double gamma() const override;
        double theta() const override;
        double speed() const override;
        double charm() const override;
        double colour() const override;
        double vega() const override;
        double rho() const override;
        double vanna() const override;
        double volga() const override;
    };

    class EuropeanPutOption : public EuropeanOption, public PutOption
    {
    public:
        EuropeanPutOption();
        ~EuropeanPutOption();
        void describe() override;
        double black_scholes_price() const;

        double delta() const override;
        double gamma() const override;
        double theta() const override;
        double speed() const override;
        double charm() const override;
        double colour() const override;
        double vega() const override;
        double rho() const override;
        double vanna() const override;
        double volga() const override;
    };

}
