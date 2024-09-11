#include "Bond.hpp"

namespace PFT
{
    namespace Securities
    {
        Bond::Bond(double maturity,
                   double interest_rate,
                   double face_value,
                   double coupon_rate,
                   int coupon_year_frequency) : maturity(maturity),
                                                interest_rate(interest_rate),
                                                face_value(face_value),
                                                coupon_rate(coupon_rate),
                                                coupon_year_frequency(coupon_year_frequency)
        {
            this->coupon_payment = this->face_value * (this->coupon_rate / this->coupon_year_frequency);
            this->maturity_payment = this->face_value + this->coupon_payment;
        }

        Bond::~Bond()
        {
        }

        auto Bond::set_maturity(double maturity) -> void
        {
            this->maturity = maturity;
        }

        auto Bond::set_interest_rate(double interest_rate) -> void
        {
            this->interest_rate = interest_rate;
        }

        auto Bond::set_face_value(double face_value) -> void
        {
            this->face_value = face_value;
        }

        auto Bond::set_coupon_rate(double coupon_rate) -> void
        {
            this->coupon_rate = coupon_rate;
        }

        auto Bond::set_coupon_year_frequency(int coupon_year_frequency) -> void
        {
            this->coupon_year_frequency = coupon_year_frequency;
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

        auto Bond::get_discounts() -> std::vector<double> *
        {
            return this->discounts;
        }

        auto Bond::price() -> double
        {

            double initial_discount = (1 / (1 + (this->interest_rate / this->coupon_year_frequency)));
            auto coupon_payment = this->coupon_payment;

            this->discounts = new std::vector<double>(this->maturity * this->coupon_year_frequency, initial_discount);

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