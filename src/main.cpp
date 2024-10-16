#include "FixedIncome/Bond.hpp"

#include <iostream>

int main()
{
    PFT::Security::FixedIncome::Annuity ann{500, 0.04, 2, 10};
    std::cout << "Current Price -> " << ann.current_price() << std::endl;

    PFT::Security::FixedIncome::Perpetuity perp{500, 0.04};
    std::cout << "Current Price -> " << perp.current_price() << std::endl;

    PFT::Security::FixedIncome::ZeroCouponBond zcb{100, 0.04, 2, 1};
    std::cout << "Current Price -> " << zcb.current_price() << std::endl;

    PFT::Security::FixedIncome::CouponBond coupon_bond{100, 0.04, 0.02, 2, 10};
    std::cout << "Current Price -> " << coupon_bond.get_asset_price() << std::endl;
}