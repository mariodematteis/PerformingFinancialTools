#pragma once

#include "../Asset.hpp"

namespace PFT::Security::Derivative
{
    class Derivative : public Asset
    {
    private:
        double maturity = 0.0;

    public:
        virtual ~Derivative() = default;
        virtual auto describe() -> void = 0;

        auto get_maturity() const -> double { return maturity; };
    };
}