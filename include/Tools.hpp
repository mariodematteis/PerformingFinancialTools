#pragma once

#include <cstdlib>
#include <cmath>

namespace PFT::Tools
{

    template <typename T>
    concept AllowedTypes = std::is_same_v<T, int> ||
                           std::is_same_v<T, double>;

    class standardize_moneyness
    {
    public:
        template <AllowedTypes T>
        auto operator()(
            const T &underlying_price,
            const T &strike_price,
            const T &interest_rate,
            const T &maturity,
            const T &current_time,
            const T &sigma,
            const T &dividend_yield) const -> double
        {
            return (
                       std::log(underlying_price / strike_price) +
                       (interest_rate - dividend_yield + (pow(sigma, 2.0) / 2)) *
                           (maturity - current_time)) /
                   (sigma * (std::sqrt(maturity - current_time)));
        }
    };

    class critical_value
    {
    public:
        template <AllowedTypes T>
        auto operator()(
            const T &underlying_price,
            const T &strike_price,
            const T &interest_rate,
            T maturity,
            T current_time,
            T sigma,
            T dividend_yield) const -> double
        {
            return (
                       std::log(underlying_price / strike_price) +
                       (interest_rate - dividend_yield + (pow(sigma, 2.0) / 2)) *
                           (maturity - current_time)) /
                       (sigma * (std::sqrt(maturity - current_time))) -
                   sigma * std::sqrt(maturity - current_time);
        }
    };

    class norm_cdf
    {
    public:
        template <AllowedTypes T>
        double operator()(T x) const
        {
            return std::erfc(-x / std::sqrt(2)) / 2;
        }
    };
}
