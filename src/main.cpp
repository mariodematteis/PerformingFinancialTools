#include <Derivative/Derivative.hpp>
#include "FixedIncome/Bond.hpp"

using namespace PFT::Security::FixedIncome;

int main()
{
    Bond bond(2,
              0.02,
              100,
              0.06,
              2);

    bond.price();

    return 0;
}