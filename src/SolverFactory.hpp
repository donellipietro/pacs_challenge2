#ifndef __SOLVER_FACTORY__
#define __SOLVER_FACTORY__

#include <memory>
#include "Solvers.hpp"

template <class SolverType, class... Args>
std::unique_ptr<SolverBase>
SolverFactory(Args &&...args) noexcept
{
    if constexpr (std::is_same_v<SolverType, Bisection>)
        try
        {
            // Possible problem: no change of sign at the ends and a new interval can not be found
            return std::make_unique<Bisection>(std::forward<Args>(args)...);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            std::cout << "Switching to Secant solver..." << std::endl;
            std::cout << std::endl;
            return SolverFactory<Secant>(std::forward<Args>(args)...);
        }

    if constexpr (std::is_same_v<SolverType, RegulaFalsi>)
        try
        {
            // Possible problem: no change of sign at the ends and a new interval can not be found
            return std::make_unique<RegulaFalsi>(std::forward<Args>(args)...);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            std::cout << "Switching to Secant solver..." << std::endl;
            std::cout << std::endl;
            return SolverFactory<Secant>(std::forward<Args>(args)...);
        }

    if constexpr (std::is_same_v<SolverType, BrentSearch>)
        try
        {
            // Possible problem: no change of sign at the ends and a new interval can not be found
            return std::make_unique<BrentSearch>(std::forward<Args>(args)...);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            std::cout << "Switching to Secant solver..." << std::endl;
            std::cout << std::endl;
            return SolverFactory<Secant>(std::forward<Args>(args)...);
        }

    if constexpr (std::is_same_v<SolverType, Secant>)
        try
        {
            // Possible problem: solver is initialized with a point instead of an interval
            auto ptr = std::make_unique<Secant>(std::forward<Args>(args)...);
            return ptr;
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            std::cout << "Switching to QuasiNewton solver..." << std::endl;
            std::cout << std::endl;
            return SolverFactory<QuasiNewton>(std::forward<Args>(args)...);
        }

    if constexpr (std::is_same_v<SolverType, Newton>)
        try
        {
            // Possible problem: Newton is initialized without the derivative of the function
            return std::make_unique<Newton>(std::forward<Args>(args)...);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            std::cout << "Switching to QuasiNewton solver..." << std::endl;
            std::cout << std::endl;
            return SolverFactory<QuasiNewton>(std::forward<Args>(args)...);
        }

    if constexpr (std::is_same_v<SolverType, QuasiNewton>)
        try
        {
            return std::make_unique<QuasiNewton>(std::forward<Args>(args)...);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
        }

    return nullptr;
}

SolverTraits::ReturnType SafeSolve(std::unique_ptr<SolverBase> &solver) noexcept
{
    SolverTraits::ReturnType result;
    try
    {
        result = solver->solve();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << std::endl;
        result = std::numeric_limits<SolverTraits::ReturnType>::quiet_NaN();
    }

    return result;
}

#endif