#ifndef __SOLVER_FACTORY__
#define __SOLVER_FACTORY__

#include <memory>
#include "Solvers.hpp"

template <class SolverType, class... Args>
std::unique_ptr<SolverBase>
SolverFactory(Args &&...args)
{
    if constexpr (std::is_same_v<SolverType, Secant>)
        return std::make_unique<Secant>(std::forward<Args>(args)...);
    if constexpr (std::is_same_v<SolverType, Bisection>)
        return std::make_unique<Bisection>(std::forward<Args>(args)...);
    if constexpr (std::is_same_v<SolverType, Newton>)
        return std::make_unique<Newton>(std::forward<Args>(args)...);
    return nullptr;
}

#endif