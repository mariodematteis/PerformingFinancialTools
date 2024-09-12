#include "FixedIncome/Bond.hpp"

namespace PFT
{
    namespace Security
    {
        namespace FixedIncome
        {
            Bond::Bond(double maturity,
                       double interest_rate,
                       double face_value,
                       double coupon_rate,
                       int coupon_year_frequency,
                       std::string symbol,
                       std::string name) : maturity(maturity),
                                           interest_rate(interest_rate),
                                           face_value(face_value),
                                           coupon_rate(coupon_rate),
                                           coupon_year_frequency(coupon_year_frequency)

            {
                this->set_asset_class(BOND_ASSET_CLASS);
                this->set_symbol(symbol);
                this->set_name(name);

                this->coupon_payment = this->face_value * (this->coupon_rate / this->coupon_year_frequency);
                this->maturity_payment = this->face_value + this->coupon_payment;
            }

            template <AllowedSecuritySpecificationType T>
            Bond::Bond(std::unordered_map<std::string, T> specification)
            {

                if (!specification.contains(MATURITY_KEY))
                {
                    this->maturity = specification[MATURITY_KEY];
                }

                if (!specification.contains(INTEREST_RATE_KEY))
                {
                    this->interest_rate = specification[INTEREST_RATE_KEY];
                }

                if (!specification.contains(FACE_VALUE_KEY))
                {
                    this->face_value = specification[FACE_VALUE_KEY];
                }

                if (!specification.contains(COUPON_RATE_KEY))
                {
                    this->coupon_rate = specification[COUPON_RATE_KEY];
                }

                if (!specification.contains(COUPON_YEAR_FREQUENCY_KEY)) // Type.checking
                {
                    this->coupon_year_frequency = specification[COUPON_YEAR_FREQUENCY_KEY];
                }

                set_asset_class(BOND_ASSET_CLASS);
                set_symbol(DEFAULT_SYMBOL);
                set_name(DEFAULT_NAME);
                this->coupon_payment = this->face_value * (this->coupon_rate / this->coupon_year_frequency);
                this->maturity_payment = this->face_value + this->coupon_payment;
            }

            Bond::Bond(std::string filename)
            {
            }

            auto Bond::get_maturity() -> double
            {
                return this->maturity;
            }

            auto Bond::get_interest_rate() -> double
            {
                return this->interest_rate;
            }

            auto Bond::get_face_value() -> double
            {
                return this->face_value;
            }

            auto Bond::get_coupon_rate() -> double
            {
                return this->coupon_rate;
            }

            auto Bond::get_coupon_year_frequency() -> int
            {
                return this->coupon_year_frequency;
            }

            auto Bond::get_maturity_payment() -> double
            {
                return this->maturity_payment;
            }

            auto Bond::get_coupon_payment() -> double
            {
                return this->coupon_payment;
            }

            auto Bond::get_discounts() -> std::shared_ptr<std::vector<double>>
            {
                return this->discounts;
            }

            auto Bond::price() -> double
            {
                double initial_discount = (1 / (1 + (this->interest_rate / this->coupon_year_frequency)));
                auto coupon_payment = this->coupon_payment;

                this->discounts = std::make_shared<std::vector<double>>(this->maturity * this->coupon_year_frequency, initial_discount);

                int i = 1;
                std::for_each(this->discounts->begin(),
                              this->discounts->end(),
                              [&i](auto &x)
                              { x = std::pow(x, i);
                            i++; });

                auto discounts_sum = this->coupon_payment * std::accumulate(this->discounts->begin(), this->discounts->end(), 0.0f);

                return discounts_sum + this->face_value * std::pow(initial_discount, this->coupon_year_frequency * this->maturity);
            }

            auto Bond::describe() -> void
            {
                std::cout << "Bond Instance" << std::endl;
            }
        }

    }

}