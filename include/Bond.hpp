#pragma once

#include <vector>
#include <numeric>
#include <iostream>

namespace PFT
{
    namespace Securities
    {
        class Bond
        {

        private:
            int coupon_year_frequency = 0;
            double coupon_rate = 0.0f;
            double face_value = 100.0f;
            double interest_rate = 0.0f;
            double maturity = 1.0f;

            double coupon_payment = 0.0f;
            double maturity_payment = 0.0f;
            std::vector<double> *discounts{};

        public:
            Bond(double maturity,
                 double interest_rate,
                 double face_value,
                 double coupon_rate,
                 int coupon_year_frequency);
            ~Bond();

            auto set_maturity(double maturity) -> void;
            auto set_interest_rate(double interest_rate) -> void;
            auto set_face_value(double face_value) -> void;
            auto set_coupon_rate(double coupon_rate) -> void;
            auto set_coupon_year_frequency(int coupon_year_frequency) -> void;

            auto get_maturity() -> double;
            auto get_interest_rate() -> double;
            auto get_face_value() -> double;
            auto get_coupon_rate() -> double;
            auto get_coupon_year_frequency() -> int;
            auto get_maturity_payment() -> double;
            auto get_coupon_payment() -> double;
            auto get_discounts() -> std::vector<double> *;

            auto price() -> double;

            auto describe() -> void;
        };
    }
}