#ifndef __SOLVERS__
#define __SOLVERS__

#include "SolverBase.hpp"

class Secant : public SolverBase
{
public:
    T::ReturnType solve() override;
};

class Bisection : public SolverBase
{
public:
    T::ReturnType solve() override;
};

class QuasiNewton : public SolverBase
{
public:
    T::ReturnType solve() override;
};

#endif // __SOLVERS__