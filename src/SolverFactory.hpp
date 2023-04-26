#ifndef __SOLVER_FACTORY__
#define __SOLVER_FACTORY__

#include <memory>
#include "Solvers.hpp"

template <class SolverType, class... Args>
std::unique_ptr<SolverBase>
SolverFactory(Args &&...args)
{
    if constexpr (std::is_same_v<SolverType, Bisection>)
        try
        {
            return std::make_unique<Bisection>(std::forward<Args>(args)...);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            std::cout << "Switching to Secant solver..." << std::endl;
            std::cout << std::endl;
            std::cout << "Ciao1" << std::endl;
            return SolverFactory<Secant>(std::forward<Args>(args)...);
        }

    if constexpr (std::is_same_v<SolverType, Secant>)
        try
        {
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

#endif