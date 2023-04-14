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
    // constructors
    SolverBase() = default;
    SolverBase(const T::FunctionType &f,
               double tol = 1e-4) : f_(f), tol_(tol) {}

    // setters
    void setFunction(const T::FunctionType &f) { f_ = f; };
    void setTollerance(double tol) { tol_ = tol; };

    // methods
    virtual T::VariableType solve() = 0;

    // destructor
    virtual ~SolverBase() = default;
};

#endif // __SOLVER_BASE__