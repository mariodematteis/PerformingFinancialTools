#pragma once

#include <functional>
#include <cmath>
#include <iostream>
#include <utility>

namespace PFT
{
    namespace Optimization
    {

        template <typename T>
        concept AllowedTypes = std::is_same_v<T, int> ||
                               std::is_same_v<T, double>;

        static const int MAXIMUM_ITERATION = 1'000'000;
        static const int DEFAULT_A = 0;
        static const int DEFAULT_B = 1;
        double tolerance = 1e-06;
        double initial_point = 0.01f;

        template <AllowedTypes T>
        auto newton(std::function<double(double)> f,
                    std::function<double(double)> df,
                    double tol = tolerance,
                    T x0 = initial_point) noexcept -> float;

        template <AllowedTypes T>
        auto newton(std::pair<std::function<double(double)>, std::function<double(double)>> function_pair,
                    double tol = tolerance,
                    T x0 = initial_point) noexcept -> float;

        template <AllowedTypes T>
        auto bisection(std::function<double(double)> f,
                       T a = DEFAULT_A,
                       T b = DEFAULT_B,
                       double tol = tolerance) noexcept -> float;

        template <AllowedTypes T>
        auto bisection(std::function<double(double)> f,
                       std::pair<T, T> interval,
                       double tol = tolerance) noexcept -> float;

        template <AllowedTypes T>
        auto secant(std::function<double(double)> f,
                    std::function<double(double)> df,
                    double tol = tolerance) noexcept -> float;
    }
}