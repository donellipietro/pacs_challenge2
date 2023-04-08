#ifndef __SOLVER_BASE__
#define __SOLVER_BASE__

#include "SolverTraits.hpp"

class SolverBase
{

public:
    using T = SolverTraits;

protected:
    T::FunctionType f_;
    T::ScalarType tol_;
    unsigned int maxIter_;

public:
    SolverBase() = default;
    SolverBase(const T::FunctionType &f,
               T::ScalarType tol = 1e-4,
               unsigned int maxIter = 150) : f_(f), tol_(tol), maxIter_(maxIter) {}

    // setters
    void setFunction(const T::FunctionType &f) { f_ = f; };
    void setTollerance(T::ScalarType tol) { tol_ = tol; };
    void setMaxIter(unsigned int maxIter) { maxIter_ = maxIter; };

    virtual T::ReturnType solve() = 0;
};

#endif // __SOLVER_BASE__