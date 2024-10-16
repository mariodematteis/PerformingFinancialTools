#include "FixedIncome/Bond.hpp"

namespace PFT::Security::FixedIncome
{

    CashFlows::CashFlows()
    {
    }

    CashFlows::CashFlows(const std::unordered_map<double, double> &cf) : cash_flows_scheme(cf)
    {
    }

    double CashFlows::current_price() const
    {
        double _current_price = 0.0;
        std::for_each(cash_flows_scheme.begin(),
                      cash_flows_scheme.end(), [&_current_price](const auto &pair)
                      { _current_price += pair.first * pair.second; });
        return _current_price;
    }

    int CashFlows::add_cash_flow(double maturity,
                                 double amount,
                                 bool override)
    {
        if (!override && cash_flows_scheme.find(maturity) != cash_flows_scheme.end())
        {
            return -1;
        }
        cash_flows_scheme[maturity] = amount;
        return 0;
    }

    void CashFlows::describe() const
    {
        if (!cash_flows_scheme.size())
            std::cout << "The Cash Flow Scheme is empty." << std::endl;
        else
        {
            std::cout << "Cash Flow Scheme" << std::endl
                      << std::endl;
            std::for_each(cash_flows_scheme.begin(),
                          cash_flows_scheme.end(),
                          [](const auto &pair)
                          {
                              std::cout << "Maturity -> " << pair.first << " - Amount -> " << pair.second << std::endl;
                          });
        }
    }

    Annuity::Annuity(double amount,
                     double interest_rate,
                     int compounding_frequency,
                     double maturity,
                     const std::string &symbol,
                     const std::string &name) : amount_(amount), interest_rate_(interest_rate), compounding_frequency_(compounding_frequency), maturity_(maturity)
    {
        set_asset_class(annuity_security_default_class);
        set_symbol(symbol);
        set_name(name);

        for (double i = 1.0 / compounding_frequency_; i <= maturity_; i += 1.0 / compounding_frequency_)
            add_cash_flow(CashFlows::operator()(
                              interest_rate, compounding_frequency, i),
                          amount_);

        set_asset_price(current_price());
    }

    Perpetuity::Perpetuity(double amount, double interest_rate) : amount_(amount), interest_rate_(interest_rate)
    {
    }

    double Perpetuity::current_price()
    {
        set_asset_price((2 * amount_) / interest_rate_);
        return get_asset_price();
    }

    ZeroCouponBond::ZeroCouponBond(double face_value,
                                   double interest_rate,
                                   int compounding_frequency,
                                   double maturity,
                                   const std::string &symbol,
                                   const std::string &name) : face_value_(face_value), interest_rate_(interest_rate), compounding_frequency_(compounding_frequency), maturity_(maturity)
    {
        set_asset_class(zcb_security_default_class);
        set_symbol(symbol);
        set_name(name);
        add_cash_flow(CashFlows::operator()(
                          interest_rate, compounding_frequency, maturity),
                      face_value);

        set_asset_price(current_price());
    }

    CouponBond::CouponBond(double face_value,
                           double interest_rate,
                           double coupon_rate,
                           int compounding_frequency,
                           double maturity,
                           const std::string &symbol,
                           const std::string &name) : face_value_(face_value),
                                                      interest_rate_(interest_rate),
                                                      coupon_rate_(coupon_rate),
                                                      compounding_frequency_(compounding_frequency),
                                                      maturity_(maturity),
                                                      coupon_amount_((face_value / compounding_frequency) * coupon_rate)
    {
        set_asset_class(coupon_bond_security_default_class);
        set_symbol(symbol);
        set_name(name);

        annuity_ = std::make_unique<Annuity>(coupon_amount_, interest_rate_, compounding_frequency_, maturity_);
        zcb_ = std::make_unique<ZeroCouponBond>(face_value_, interest_rate_, compounding_frequency_, maturity_);

        set_asset_price(annuity_->get_asset_price() + zcb_->get_asset_price());
    }

    template <PFT::Tools::AllowedTypes T>
    Bond::Bond(T maturity,
               T interest_rate,
               T face_value,
               T coupon_rate,
               int coupon_year_frequency,
               const std::string &symbol,
               const std::string &name) : maturity(maturity),
                                          interest_rate(interest_rate),
                                          face_value(face_value),
                                          coupon_rate(coupon_rate),
                                          coupon_year_frequency(coupon_year_frequency)

    {
        set_asset_class(bond_security_default_class);
        set_symbol(symbol);
        set_name(name);

        coupon_payment = face_value * (coupon_rate / coupon_year_frequency);
        maturity_payment = face_value + coupon_payment;
    }

    template <AllowedSecuritySpecificationType T>
    Bond::Bond(const std::unordered_map<std::string, T> &specification)
    {

        if (!specification.contains(MATURITY_KEY))
        {
            maturity = specification[MATURITY_KEY];
        }

        if (!specification.contains(INTEREST_RATE_KEY))
        {
            interest_rate = specification[INTEREST_RATE_KEY];
        }

        if (!specification.contains(FACE_VALUE_KEY))
        {
            face_value = specification[FACE_VALUE_KEY];
        }

        if (!specification.contains(COUPON_RATE_KEY))
        {
            coupon_rate = specification[COUPON_RATE_KEY];
        }

        if (!specification.contains(COUPON_YEAR_FREQUENCY_KEY)) // Type.checking
        {
            coupon_year_frequency = specification[COUPON_YEAR_FREQUENCY_KEY];
        }

        set_asset_class(bond_security_default_class);
        set_symbol(DEFAULT_SYMBOL);
        set_name(DEFAULT_NAME);
        coupon_payment = face_value * (coupon_rate / coupon_year_frequency);
        maturity_payment = face_value + coupon_payment;
    }

    Bond::Bond(const std::string &filename)
    {
    }

    double Bond::get_maturity() const
    {
        return maturity;
    }

    double Bond::get_interest_rate() const
    {
        return interest_rate;
    }

    double Bond::get_face_value() const
    {
        return face_value;
    }

    double Bond::get_coupon_rate() const
    {
        return coupon_rate;
    }

    int Bond::get_coupon_year_frequency() const
    {
        return coupon_year_frequency;
    }

    double Bond::get_maturity_payment() const
    {
        return maturity_payment;
    }

    double Bond::get_coupon_payment() const
    {
        return coupon_payment;
    }

    std::shared_ptr<std::vector<double>> Bond::get_discounts() const
    {
        return discounts;
    }

    std::string Bond::to_string() const
    {
        return std::vformat(FORMAT_BOND, std::make_format_args(maturity, face_value));
    }

    std::unique_ptr<Security> Bond::clone() const
    {
        return std::make_unique<Bond>(*this);
    }

}