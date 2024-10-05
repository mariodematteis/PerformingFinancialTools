#pragma once

#include "Asset.hpp"
#include "../Tools.hpp"

#include <format>
#include <vector>
#include <numeric>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace PFT::Security::FixedIncome
{
    static const std::string BOND_ASSET_CLASS = "bond";

    static const std::string MATURITY_KEY = "maturity";
    static const std::string COUPON_RATE_KEY = "coupon_rate";
    static const std::string FACE_VALUE_KEY = "face_value";
    static const std::string INTEREST_RATE_KEY = "interest_rate";
    static const std::string COUPON_YEAR_FREQUENCY_KEY = "coupon_year_frequency";

    static const std::string_view FORMAT_BOND = "Bond Sheet Information\n\nMaturity -> \t {}\nFace Value -> \t {}";

    class Bond : public Asset
    {

    private:
        int coupon_year_frequency = 0;
        double coupon_rate = 0.0f;
        double face_value = 100.0f;
        double interest_rate = 0.0f;
        double maturity = 1.0f;

        double coupon_payment = 0.0f;
        double maturity_payment = 0.0f;
        double ytm = 0.0;
        std::shared_ptr<std::vector<double>>
            discounts;

    public:
        template <PFT::Tools::AllowedTypes T>
        Bond(T maturity,
             T interest_rate,
             T face_value,
             T coupon_rate,
             int coupon_year_frequency,
             std::string symbol = DEFAULT_SYMBOL,
             std::string name = DEFAULT_NAME);

        template <AllowedSecuritySpecificationType T>
        Bond(std::unordered_map<std::string, T> specification);
        Bond(std::string filename);

        virtual ~Bond() = default;

        auto get_maturity() const -> double;
        auto get_interest_rate() const -> double;
        auto get_face_value() const -> double;
        auto get_coupon_rate() const -> double;
        auto get_coupon_year_frequency() const -> int;
        auto get_maturity_payment() const -> double;
        auto get_coupon_payment() const -> double;
        auto get_discounts() const -> std::shared_ptr<std::vector<double>>;

        virtual auto price() -> double;
        virtual auto yield_to_maturity() -> double;

        std::string to_string() const override;
        std::unique_ptr<Asset> clone() const override;
    };
}