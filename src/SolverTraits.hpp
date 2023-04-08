#ifndef __SOLVER_TRAITS__
#define __SOLVER_TRAITS__

#include <functional>

struct SolverTraits
{
    using ScalarType = double;
    using VariableType = double;
    using ReturnType = double;
    using FunctionType = std::function<ReturnType(const VariableType &)>;
};

#endif // __SOLVER_TRAITS__
