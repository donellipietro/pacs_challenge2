#ifndef __SOLVER_BASE__
#define __SOLVER_BASE__

#include "SolverTraits.hpp"

class SolverBase
{

public:
    using T = SolverTraits;

protected:
    T::FunctionType f_;
    double tol_;

public:
    SolverBase() = default;
    SolverBase(const T::FunctionType &f,
               double tol = 1e-4) : f_(f), tol_(tol) {}

    // setters
    void setFunction(const T::FunctionType &f) { f_ = f; };
    void setTollerance(double tol) { tol_ = tol; };

    virtual T::VariableType solve() = 0;
};

#endif // __SOLVER_BASE__