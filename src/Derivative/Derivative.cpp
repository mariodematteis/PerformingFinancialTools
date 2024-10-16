#include "Derivative/Option.hpp"

namespace PFT::Security::Derivative
{

    EuropeanCallOption::EuropeanCallOption()
    {
        set_asset_class(european_call_option_default_class);
    }

    void EuropeanCallOption::describe()
    {
        std::cout << std::vformat(option_description, std::make_format_args()) << std::endl;
    }

    double EuropeanCallOption::black_scholes_price() const
    {
    }

    double EuropeanCallOption::delta() const
    {
    }

    double EuropeanCallOption::gamma() const
    {
    }

    double EuropeanCallOption::theta() const
    {
    }

    double EuropeanCallOption::speed() const
    {
    }

    double EuropeanCallOption::charm() const
    {
    }

    double EuropeanCallOption::colour() const
    {
    }

    double EuropeanCallOption::vega() const
    {
    }

    double EuropeanCallOption::rho() const
    {
    }
    double EuropeanCallOption::vanna() const
    {
    }
    double EuropeanCallOption::volga() const
    {
    }

    EuropeanPutOption::EuropeanPutOption()
    {
        set_asset_class(european_put_option_default_class);
    }

    double EuropeanPutOption::delta() const
    {
    }

    double EuropeanPutOption::gamma() const
    {
    }

    double EuropeanPutOption::theta() const
    {
    }

    double EuropeanPutOption::speed() const
    {
    }

    double EuropeanPutOption::charm() const
    {
    }

    double EuropeanPutOption::colour() const
    {
    }

    double EuropeanPutOption::vega() const
    {
    }

    double EuropeanPutOption::rho() const
    {
    }
    double EuropeanPutOption::vanna() const
    {
    }
    double EuropeanPutOption::volga() const
    {
    }

}