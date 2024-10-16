#pragma once

#include "Security.hpp"
#include "../Tools.hpp"

#include <array>
#include <algorithm>
#include <format>
#include <vector>
#include <numeric>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace PFT::Security::FixedIncome
{
    static const std::string bond_security_default_class = "bond";
    static const std::string annuity_security_default_class = "annuity";
    static const std::string perpetuity_security_default_class = "perpetuity";
    static const std::string zcb_security_default_class = "zero_coupon_bond";
    static const std::string coupon_bond_security_default_class = "coupon_bond";

    static const std::string MATURITY_KEY = "maturity";
    static const std::string COUPON_RATE_KEY = "coupon_rate";
    static const std::string FACE_VALUE_KEY = "face_value";
    static const std::string INTEREST_RATE_KEY = "interest_rate";
    static const std::string COUPON_YEAR_FREQUENCY_KEY = "coupon_year_frequency";

    static const std::string_view FORMAT_BOND = "Bond Sheet Information\n\nMaturity -> \t {}\nFace Value -> \t {}";

    class CashFlows
    {
    private:
        std::unordered_map<double, double> cash_flows_scheme;

    public:
        CashFlows();
        CashFlows(const std::unordered_map<double, double> &cf);

        double operator()(double annual_interest_rate,
                          int compounding_frequency,
                          double maturity = 0.0) const
        {
            double power = compounding_frequency * maturity;
            if (!maturity)
                power = 1.0;

            return std::pow((1 / (1 + annual_interest_rate / compounding_frequency)), power);
        }

        double current_price() const;
        int add_cash_flow(
            double maturity,
            double amount,
            bool override = false);

        void describe() const;
        std::unique_ptr<std::unordered_map<double, double>> get_cash_flows_scheme()
        {
            return std::make_unique<std::unordered_map<double, double>>(cash_flows_scheme);
        }
    };

    class Annuity : public Security, public CashFlows
    {
    private:
        const double amount_;
        const double interest_rate_;
        const int compounding_frequency_;
        const double maturity_;

    public:
        Annuity(double amount,
                double interest_rate,
                int compounding_frequency,
                double maturity,
                const std::string &symbol = DEFAULT_SYMBOL,
                const std::string &name = DEFAULT_NAME);
    };

    class Perpetuity : public Security
    {
    private:
        double amount_;
        double interest_rate_;

    public:
        Perpetuity(double amount,
                   double interest_rate);

        double current_price();
    };

    class ZeroCouponBond : public Security, public CashFlows
    {
    private:
        const double face_value_;
        const double interest_rate_;
        const int compounding_frequency_;
        const double maturity_;

    public:
        ZeroCouponBond(double face_value,
                       double interest_rate,
                       int compounding_frequency,
                       double maturity,
                       const std::string &symbol = DEFAULT_SYMBOL,
                       const std::string &name = DEFAULT_NAME);
    };

    class CouponBond : public Security
    {
    private:
        const double face_value_;
        const double interest_rate_;
        const double coupon_rate_;
        const int compounding_frequency_;
        const double maturity_;
        const double coupon_amount_;

        std::unique_ptr<Annuity> annuity_;
        std::unique_ptr<ZeroCouponBond> zcb_;

    public:
        CouponBond(double face_value,
                   double interest_rate,
                   double coupon_rate,
                   int compounding_frequency,
                   double maturity,
                   const std::string &symbol = DEFAULT_SYMBOL,
                   const std::string &name = DEFAULT_NAME);
    };

    class Bond : public Security
    {

    private:
        int coupon_year_frequency = 0;
        double coupon_rate = 0.0;
        double face_value = 100.0;
        double interest_rate = 0.0;
        double maturity = 1.0;

        double coupon_payment = 0.0;
        double maturity_payment = 0.0;
        double ytm = 0.0;
        std::shared_ptr<std::vector<double>> discounts;

    public:
        template <PFT::Tools::AllowedTypes T>
        Bond(T maturity,
             T interest_rate,
             T face_value,
             T coupon_rate,
             int coupon_year_frequency,
             const std::string &symbol = DEFAULT_SYMBOL,
             const std::string &name = DEFAULT_NAME);

        template <PFT::Security::AllowedSecuritySpecificationType T>
        Bond(const std::unordered_map<std::string, T> &specification);
        Bond(const std::string &filename);

        virtual double price() const { return 0.0; }
        virtual double yield_to_maturity() const { return 0.0; }

        virtual ~Bond() = default;

        double get_maturity() const;
        double get_interest_rate() const;
        double get_face_value() const;
        double get_coupon_rate() const;
        int get_coupon_year_frequency() const;
        double get_maturity_payment() const;
        double get_coupon_payment() const;
        std::shared_ptr<std::vector<double>> get_discounts() const;

        std::string to_string() const;
        std::unique_ptr<Security> clone() const;
    };
}