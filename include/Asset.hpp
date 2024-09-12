#pragma once

#include <string>
#include <chrono>

namespace PFT
{
    namespace Security
    {
        template <typename T>
        concept AllowedSecuritySpecificationType = std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, std::string>;

        static const std::string DEFAULT_SYMBOL = "undefined";
        static const std::string DEFAULT_NAME = "undefined";

        class Asset
        {
        private:
            std::string _asset_class;
            std::string _symbol;
            std::string _name;

            double _asset_price = 0.0;

        public:
            auto get_symbol() const -> std::string { return _symbol; }
            auto get_name() const -> std::string { return _name; }
            auto get_asset_class() const -> std::string { return _asset_class; }
            auto get_asset_price() const -> double { return _asset_price; }

            auto set_asset_class(std::string asset_class) -> void { _asset_class = asset_class; }
            auto set_symbol(std::string symbol) -> void { _symbol = symbol; }
            auto set_name(std::string name) -> void { _name = name; }
            auto set_asset_price(double asset_price) -> void { _asset_price = asset_price; }
        };
    }
}