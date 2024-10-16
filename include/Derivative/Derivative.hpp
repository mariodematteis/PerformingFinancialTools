#pragma once

#include "../Security.hpp"

namespace PFT::Security::Derivative
{
    class Derivative : public PFT::Security::Security
    {
    private:
        const double maturity = 0.0;

    public:
        virtual ~Derivative() = default;
        virtual void describe() = 0;

        double get_maturity() const { return maturity; };
    };
}