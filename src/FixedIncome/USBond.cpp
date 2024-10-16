#include "FixedIncome/USBond.hpp"

namespace PFT::Security::FixedIncome::USBond
{
    TreasuryBond::TreasuryBond(double maturity, double interest_rate, double face_value,
                               double coupon_rate, int coupon_year_frequency,
                               std::string auction_date, std::string issue_date, std::string cusip,
                               std::string symbol, std::string name)
        : Bond(maturity, interest_rate, face_value, coupon_rate, coupon_year_frequency, symbol, name),
          auction_date(std::move(auction_date)),
          issue_date(std::move(issue_date)),
          cusip(std::move(cusip))
    {
    }

    TreasuryBill::TreasuryBill(double maturity, double face_value, double discount_rate,
                               std::string issue_date, std::string cusip,
                               std::string symbol, std::string name)
        : Bond(maturity, 0.0, face_value, 0.0, 0.0, symbol, name), // T-Bills don't have coupons
          discount_rate(discount_rate), issue_date(std::move(issue_date)), cusip(std::move(cusip))
    {
    }

    double TreasuryBill::get_discount_rate() const
    {
        return discount_rate;
    }

    std::string TreasuryBill::get_issue_date() const
    {
        return issue_date;
    }

    std::string TreasuryBill::get_cusip() const
    {
        return cusip;
    }

    double TreasuryBill::yield_to_maturity() const
    {
        double p = price();
        return (get_face_value() - p) / p * (360 / get_maturity()); // Bank discount yield
    }

    std::string TreasuryBill::to_string() const
    {
        return std::format("{}\nDiscount Rate: {:.2f}%\nIssue Date: {}\nCUSIP: {}",
                           Bond::to_string(), discount_rate * 100, issue_date, cusip);
    }

    std::unique_ptr<Security> TreasuryBill::clone() const
    {
        return std::make_unique<TreasuryBill>(*this);
    }

    TreasuryNote::TreasuryNote(double maturity, double interest_rate, double face_value,
                               double coupon_rate, int coupon_year_frequency,
                               std::string issue_date, std::string cusip,
                               std::string symbol, std::string name)
        : Bond(maturity, interest_rate, face_value, coupon_rate, coupon_year_frequency, symbol, name),
          issue_date(std::move(issue_date)), cusip(std::move(cusip)) {}

    std::string TreasuryNote::get_issue_date() const
    {
        return issue_date;
    }

    std::string TreasuryNote::get_cusip() const
    {
        return cusip;
    }

    double TreasuryNote::price() const
    {
        double price = 0.0;
        double r = get_interest_rate() / get_coupon_year_frequency();
        int periods = static_cast<int>(get_maturity() * get_coupon_year_frequency());

        for (int i = 1; i <= periods; ++i)
        {
            price += (get_coupon_rate() * get_face_value() / get_coupon_year_frequency()) / std::pow(1 + r, i);
        }
        price += get_face_value() / std::pow(1 + r, periods);

        return price;
    }

    double TreasuryNote::yield_to_maturity() const
    {
        // Implement numerical method (e.g., Newton-Raphson) to solve for YTM
        // This is a simplified placeholder
        return (get_coupon_rate() * get_face_value() + (get_face_value() - price()) / get_maturity()) /
               ((get_face_value() + price()) / 2);
    }

    std::string TreasuryNote::to_string() const
    {
        return std::format("{}\nIssue Date: {}\nCUSIP: {}",
                           Bond::to_string(), issue_date, cusip);
    }

    std::unique_ptr<Security> TreasuryNote::clone() const
    {
        return std::make_unique<TreasuryNote>(*this);
    }

    TIPS::TIPS(double maturity, double interest_rate, double face_value,
               double coupon_rate, int coupon_year_frequency,
               double inflation_rate,
               std::string symbol, std::string name)
        : Bond(maturity, interest_rate, face_value, coupon_rate, coupon_year_frequency, symbol, name),
          inflation_rate(inflation_rate)
    {
        // Initialize inflation adjustments
        inflation_adjustments.resize(static_cast<size_t>(maturity * coupon_year_frequency), 1.0);
    }

    double TIPS::get_inflation_rate() const
    {
        return inflation_rate;
    }

    void TIPS::set_inflation_rate(double new_rate)
    {
        inflation_rate = new_rate;
        // Recalculate inflation adjustments
        for (size_t i = 0; i < inflation_adjustments.size(); ++i)
        {
            inflation_adjustments[i] = std::pow(1 + inflation_rate, static_cast<double>(i) / get_coupon_year_frequency());
        }
    }

    double TIPS::get_adjusted_face_value() const
    {
        return get_face_value() * inflation_adjustments.back();
    }

    double TIPS::get_adjusted_coupon_payment() const
    {
        return (get_coupon_rate() * get_face_value() / get_coupon_year_frequency()) * inflation_adjustments.back();
    }

    double TIPS::price() const
    {
        double price = 0.0;
        double r = get_interest_rate() / get_coupon_year_frequency();

        for (size_t i = 0; i < inflation_adjustments.size(); ++i)
        {
            double coupon = get_adjusted_coupon_payment() * inflation_adjustments[i];
            price += coupon / std::pow(1 + r, i + 1);
        }
        price += get_adjusted_face_value() / std::pow(1 + r, inflation_adjustments.size());

        return price;
    }

    double TIPS::yield_to_maturity() const
    {
        // Implement numerical method (e.g., Newton-Raphson) to solve for YTM
        // This is a simplified placeholder
        return (get_adjusted_coupon_payment() * get_coupon_year_frequency() +
                (get_adjusted_face_value() - price()) / get_maturity()) /
               ((get_adjusted_face_value() + price()) / 2);
    }

    std::string TIPS::to_string() const
    {
        return std::format("{}\nInflation Rate: {:.2f}%\nAdjusted Face Value: ${:.2f}",
                           Bond::to_string(), inflation_rate * 100, get_adjusted_face_value());
    }

    std::unique_ptr<Security> TIPS::clone() const
    {
        return std::make_unique<TIPS>(*this);
    }

    MunicipalBond::MunicipalBond(double maturity,
                                 double interest_rate,
                                 double face_value,
                                 double coupon_rate,
                                 int coupon_year_frequency,
                                 bool tax_exempt,
                                 std::string state,
                                 std::string symbol,
                                 std::string name)
        : Bond(maturity, interest_rate, face_value, coupon_rate, coupon_year_frequency, symbol, name),
          tax_exempt(tax_exempt), state(state)
    {
    }

    bool MunicipalBond::is_tax_exempt() const
    {
        return tax_exempt;
    }

    std::string MunicipalBond::get_state() const
    {
        return state;
    }

    std::string MunicipalBond::to_string() const
    {
        return std::format("{}\nTax Exempt: {}\nState: {}",
                           Bond::to_string(), tax_exempt ? "Yes" : "No", state);
    }

    std::unique_ptr<Security> MunicipalBond::clone() const
    {
        return std::make_unique<MunicipalBond>(*this);
    }

    auto MunicipalBond::calculate_taxable_equivalent_yield(double tax_rate) const -> double
    {
        if (tax_exempt)
        {
            return get_coupon_rate() / (1 - tax_rate);
        }
        return get_coupon_rate();
    }

}