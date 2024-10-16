#include "Method/Optimization.hpp"

namespace PFT::Methods::Optimization
{
    template <typename T>
    auto newton(std::function<double(double)> f,
                std::function<double(double)> df,
                const double& x0,
                const double& tolerance) noexcept -> float
    {
        double x = x0;
        for (int i = 0; i < MAXIMUM_ITERATION; i++)
        {
            double fx = f(x);
            if (std::abs(fx) < tolerance)
                return fx;

            double dfx = df(x);
            if (!dfx)
                std::cout << "Derivative 0 at point X = " << x << std::endl;
            x = x - fx / dfx;
        }
        std::cout << "Unable to converge." << std::endl;
        return x;
    }

    template <PFT::Tools::AllowedTypes T>
    auto newton(std::pair<std::function<double(double)>, std::function<double(double)>> function_pair,
                const double& tolerance,
                const T& x0) noexcept -> float
    {
        auto &f = function_pair.first;
        auto &df = function_pair.second;

        double x = x0;
        for (int i = 0; i < MAXIMUM_ITERATION; i++)
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

    template <PFT::Tools::AllowedTypes T>
    auto bisection(std::function<double(double)> f,
                    const T& a,
                    const T& b,
                    double tol) noexcept -> float
    {
    }

    template <PFT::Tools::AllowedTypes T>
    auto bisection(const std::function<double(double)>& f,
                   const std::pair<T, T>& interval,
                   const double& tol) noexcept -> float
    {
    }

    template <typename T>
    auto secant(const T &function,
                const T &derivative,
                const double& tolerance) noexcept -> float
    {
    }

}
