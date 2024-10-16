#pragma once

#include <string>
#include <chrono>

namespace PFT::Security
{
    template <typename T>
    concept AllowedSecuritySpecificationType = std::is_same_v<T, int> ||
                                               std::is_same_v<T, double> ||
                                               std::is_same_v<T, std::string>;

    static const std::string default_symbol = "undefined";
    static const std::string default_name = "undefined";

    /*
    Security generally defines any types of tradable financial instruments.
    Among the various types of security:
    - Equity Securities (e.g., Common Stock)
    - Debt Securities (e.g., Bonds)
    - Derivative Contracts
    */
    class Security
    {
    private:
        std::string asset_class_;
        std::string symbol_;
        std::string name_;

        double asset_price_ = 0.0;

    public:
        auto get_symbol() const -> const std::string & { return symbol_; }
        auto get_name() const -> const std::string & { return name_; }
        auto get_asset_class() const -> const std::string & { return asset_class_; }
        auto get_asset_price() const -> double { return asset_price_; }

        auto set_asset_class(const std::string &asset_class) -> void { asset_class_ = asset_class; }
        auto set_symbol(const std::string &symbol) -> void { symbol_ = symbol; }
        auto set_name(const std::string &name) -> void { name_ = name; }
        auto set_asset_price(double asset_price) -> void { asset_price_ = asset_price; }
    };
}
