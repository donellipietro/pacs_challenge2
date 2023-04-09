#ifndef __SOLVERS__
#define __SOLVERS__

#include "SolverBase.hpp"

class Secant : public SolverBase
{
private:
    T::VariableType a_;
    T::VariableType b_;
    double tola_;
    unsigned int maxIter_;

public:
    // constructors
    Secant() = default;
    Secant(const T::FunctionType &f,
           T::VariableType a,
           T::VariableType b,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150) : SolverBase(f, tol), a_(a), b_(b), tola_(tola), maxIter_(maxIter) {}

    // setters
    void setAbsoluteTollerance(double tola) { tola_ = tola; };
    void setA(T::VariableType a) { a_ = a; };
    void setB(T::VariableType b) { b_ = b; };

    // methods
    T::VariableType solve() override;
};

class Bisection : public SolverBase
{
private:
    T::VariableType a_;
    T::VariableType b_;

public:
    // constructors
    Bisection() = default;
    Bisection(const T::FunctionType &f,
              T::VariableType a,
              T::VariableType b,
              double tol = 1e-4,
              unsigned int maxIter = 150) : SolverBase(f, tol), a_(a), b_(b) {}

    // setters
    void setA(T::VariableType a) { a_ = a; };
    void setB(T::VariableType b) { b_ = b; };

    // methods
    T::VariableType solve() override;
};

class Newton : public SolverBase
{

private:
    T::FunctionType df_;
    T::VariableType x0_;
    double tola_;
    unsigned int maxIter_;

public:
    // constructors
    Newton();
    Newton(const T::FunctionType &f,
           const T::FunctionType &df,
           T::VariableType x0,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150) : SolverBase(f, tol), df_(df), x0_(x0), tola_(tola), maxIter_(maxIter) {}

    // setters
    void setDerivative(T::FunctionType df) { df_ = df; };
    void setAbsoluteTollerance(double tola) { tola_ = tola; };
    void setInitializationPoint(T::VariableType x0) { x0_ = x0; };

    // methods
    T::VariableType solve() override;
};

#endif // __SOLVERS__