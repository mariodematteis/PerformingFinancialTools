#include "Optimization.hpp"

namespace PFT
{
    namespace Optimization
    {
        template <typename T>
        auto newton(std::function<double(double)> f,
                    std::function<double(double)> df,
                    double x0,
                    double tolerance) noexcept -> float
        {
            double x = x0;
            for (int i = 0; i < PFT::Optimization::MAXIMUM_ITERATION; i++)
            {
                double fx = f(x);
                if (std::abs(fx) < tolerance)
                {
                    return fx;
                }

                double dfx = df(x);
                if (!dfx)
                    std::cout << "Derivative 0 at point X = " << x << std::endl;
                x = x - fx / dfx;
            }
            std::cout << "Unable to converge." << std::endl;
            return x;
        }

        template <AllowedTypes T>
        auto newton(std::pair<std::function<double(double)>,
                              std::function<double(double)>>
                        function_pair,
                    double tolerance,
                    T x0) noexcept -> float
        {
            auto &f = function_pair.first;
            auto &df = function_pair.second;

            double x = x0;
            for (int i = 0; i < PFT::Optimization::MAXIMUM_ITERATION; i++)
            {
                double fx = f(x);
                if (std::abs(fx) < tolerance)
                {
                    return fx;
                }

                double dfx = df(x);
                if (!dfx)
                    std::cout << "Derivative 0 at point X = " << x << std::endl;
                x = x - fx / dfx;
            }
            std::cout << "Unable to converge." << std::endl;
            return x;
        }

        template <AllowedTypes T>
        auto bisection(std::function<double(double)> f,
                       T a,
                       T b,
                       double tol) noexcept -> float
        {
        }

        template <AllowedTypes T>
        auto bisection(std::function<double(double)> f,
                       std::pair<T, T> interval,
                       double tol) noexcept -> float
        {
        }

        template <typename T>
        auto secant(T &function, T &derivative, double tolerance) noexcept -> float
        {
        }

    }

}