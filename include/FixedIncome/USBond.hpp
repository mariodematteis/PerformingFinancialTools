#pragma once

#include "Bond.hpp"

namespace PFT::Security::FixedIncome::USBond
{
    class TreasuryBond : public Bond
    {
    private:
        std::string auction_date;
        std::string issue_date;
        std::string cusip;

    public:
        TreasuryBond(double maturity,
                     double interest_rate,
                     double face_value,
                     double coupon_rate,
                     int coupon_year_frequency,
                     std::string auction_date, std::string issue_date, std::string cusip,
                     std::string symbol = DEFAULT_SYMBOL, std::string name = DEFAULT_NAME);

        double price() const override;
        double yield_to_maturity() const override;

        std::string get_auction_date() const
        {
            return auction_date;
        }
        std::string get_issue_date() const { return issue_date; }
        std::string get_cusip() const { return cusip; }
    };

    class TreasuryBill : public Bond
    {
    private:
        double discount_rate;
        std::string issue_date;
        std::string cusip;

    public:
        TreasuryBill(double maturity,
                     double face_value,
                     double discount_rate,
                     std::string issue_date,
                     std::string cusip,
                     std::string symbol = DEFAULT_SYMBOL, std::string name = DEFAULT_NAME);

        double price() const override;
        double yield_to_maturity() const override;

        double get_discount_rate() const;
        std::string get_issue_date() const;
        std::string get_cusip() const;

        std::string to_string() const;
        std::unique_ptr<Security> clone() const;
    };

    class TreasuryNote : public Bond
    {
    private:
        std::string issue_date;
        std::string cusip;

    public:
        TreasuryNote(double maturity,
                     double interest_rate,
                     double face_value,
                     double coupon_rate,
                     int coupon_year_frequency,
                     std::string issue_date,
                     std::string cusip,
                     std::string symbol = DEFAULT_SYMBOL,
                     std::string name = DEFAULT_NAME);

        double price() const override;
        double yield_to_maturity() const override;

        std::string get_issue_date() const;
        std::string get_cusip() const;

        std::string to_string() const;
        std::unique_ptr<Security> clone() const;
    };

    class TIPS : public Bond
    {
    private:
        double inflation_rate;
        std::vector<double> inflation_adjustments;

    public:
        TIPS(double maturity,
             double interest_rate,
             double face_value,
             double coupon_rate,
             int coupon_year_frequency,
             double inflation_rate,
             std::string symbol = DEFAULT_SYMBOL,
             std::string name = DEFAULT_NAME);

        double price() const override;
        double yield_to_maturity() const override;

        double get_inflation_rate() const;
        double get_adjusted_face_value() const;
        double get_adjusted_coupon_payment() const;

        void set_inflation_rate(double new_rate);

        std::string to_string() const;
        std::unique_ptr<Security> clone() const;
    };

    class MunicipalBond : public Bond
    {
    private:
        bool tax_exempt;
        std::string state;

    public:
        MunicipalBond(double maturity,
                      double interest_rate,
                      double face_value,
                      double coupon_rate,
                      int coupon_year_frequency,
                      bool tax_exempt,
                      std::string state,
                      std::string symbol = DEFAULT_SYMBOL,
                      std::string name = DEFAULT_NAME);

        double price() const override;
        double yield_to_maturity() const override;

        bool is_tax_exempt() const;
        std::string get_state() const;

        double calculate_taxable_equivalent_yield(double tax_rate) const;

        std::string to_string() const;
        std::unique_ptr<Security> clone() const;
    };
}