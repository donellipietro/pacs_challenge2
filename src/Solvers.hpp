#ifndef __SOLVERS__
#define __SOLVERS__

#include "SolverBase.hpp"

void checkChangeOfSign(const SolverTraits::FunctionType &f,
                       SolverTraits::VariableType &a, SolverTraits::VariableType &b);

std::tuple<SolverTraits::VariableType, SolverTraits::VariableType, bool>
bracketInterval(const SolverTraits::FunctionType &f, SolverTraits::VariableType x1,
                double h = 0.01, unsigned int maxIter = 200);

double finiteDiff(const SolverTraits::FunctionType &f, const SolverTraits::VariableType x, const double h = 0.001);

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
              unsigned int maxIter = 150) : SolverBase(f, tol), a_(a), b_(b)
    {
        checkChangeOfSign(f_, a_, b_);
    }

    // setters
    void setA(T::VariableType a) { a_ = a; };
    void setB(T::VariableType b) { b_ = b; };

    // methods
    T::VariableType solve() override;
};

class Newton : public SolverBase
{

protected:
    T::FunctionType df_;
    T::VariableType x0_;
    double tola_;
    unsigned int maxIter_;

public:
    // constructors
    Newton() = default;
    Newton(const T::FunctionType &f,
           const T::FunctionType &df,
           T::VariableType x0,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150) : SolverBase(f, tol), df_(df), x0_(x0), tola_(tola), maxIter_(maxIter) {}

    // setters
    void setDerivative(T::FunctionType df) { df_ = df; };
    void setInitializationPoint(T::VariableType x0) { x0_ = x0; };
    void setAbsoluteTollerance(double tola) { tola_ = tola; };
    void setMaxIter(unsigned int maxIter) { maxIter_ = maxIter; };

    // methods
    T::VariableType solve() override;
};

class QuasiNewton : public Newton
{

public:
    // constructors
    QuasiNewton();
    QuasiNewton(const T::FunctionType &f,
                T::VariableType x0,
                double tol = 1e-4,
                double tola = 1e-10,
                unsigned int maxIter = 150)
    {
        setFunction(f);
        setTollerance(tol);
        setInitializationPoint(x0);
        setDerivative(T::FunctionType([this](const T::VariableType x)
                                      { return finiteDiff(f_, x); }));
        setAbsoluteTollerance(tola);
        setMaxIter(maxIter);
    }

    // setters
    void setAbsoluteTollerance(double tola) { tola_ = tola; };
    void setInitializationPoint(T::VariableType x0) { x0_ = x0; };
};

#endif // __SOLVERS__