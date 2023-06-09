#ifndef __SOLVERS__
#define __SOLVERS__

#include "SolverBase.hpp"
#include <array>
#include <limits>

void checkChangeOfSign(const SolverTraits::FunctionType &f,
                       SolverTraits::VariableType &a, SolverTraits::VariableType &b);

void searchBracketInterval(const SolverTraits::FunctionType &f,
                           SolverTraits::VariableType x1, SolverTraits::VariableType &a, SolverTraits::VariableType &b);

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
           T::VariableType x1,
           double tol = 1e-4,
           unsigned int maxIter = 150) : SolverBase(f, tol)
    {
        throw std::invalid_argument("Secant method requires an interval but only one point has been provided!");
    }
    Secant(const T::FunctionType &f,
           std::array<T::VariableType, 2> interval,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150)
        : SolverBase(f, tol), a_(interval[0]), b_(interval[1]), tola_(tola), maxIter_(maxIter) {}

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
              T::VariableType x1,
              double tol = 1e-4) : SolverBase(f, tol)
    {
        searchBracketInterval(f_, x1, a_, b_);
    }
    Bisection(const T::FunctionType &f, std::array<T::VariableType, 2> interval, double tol = 1e-4)
        : SolverBase(f, tol), a_(interval[0]), b_(interval[1])
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
           T::VariableType x0,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150)
    {
        throw std::invalid_argument("You asked for Newton solver but the derivative of the function has not been provided!");
    }
    Newton(const T::FunctionType &f,
           std::array<T::VariableType, 2> interval,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150)
    {
        throw std::invalid_argument("You asked for Newton solver but the derivative of the function has not been provided!");
    }
    Newton(const T::FunctionType &f,
           const T::FunctionType &df,
           T::VariableType x0,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150) : SolverBase(f, tol), df_(df), x0_(x0), tola_(tola), maxIter_(maxIter) {}
    Newton(const T::FunctionType &f,
           const T::FunctionType &df,
           std::array<T::VariableType, 2> interval,
           double tol = 1e-4,
           double tola = 1e-10,
           unsigned int maxIter = 150) : Newton(f, interval[0], tol, tola, maxIter){};

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
                std::array<T::VariableType, 2> interval,
                double tol = 1e-4,
                double tola = 1e-10,
                unsigned int maxIter = 150) : QuasiNewton(f, interval[0], tol, tola, maxIter){};
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
    // If the derivative is provided QuasiNewton == Newton
    // This redoundancy is needed becasuse to be able to switch from Newton to QuasiNewton
    // in the factory we need a compatible constructor.
    QuasiNewton(const T::FunctionType &f,
                const T::FunctionType &df,
                T::VariableType x0,
                double tol = 1e-4,
                double tola = 1e-10,
                unsigned int maxIter = 150) : Newton(f, df, x0, tol, tola, maxIter){};
};

class RegulaFalsi : public SolverBase
{
private:
    T::VariableType a_;
    T::VariableType b_;
    double tola_;

public:
    // constructors
    RegulaFalsi() = default;
    RegulaFalsi(const T::FunctionType &f,
                T::VariableType x1,
                double tol = 1e-4,
                double tola = 1e-10) : SolverBase(f, tol), tola_(tola)
    {
        searchBracketInterval(f_, x1, a_, b_);
    }
    RegulaFalsi(const T::FunctionType &f, std::array<T::VariableType, 2> interval, double tol = 1e-4, double tola = 1e-10)
        : SolverBase(f, tol), a_(interval[0]), b_(interval[1]), tola_(tola)
    {
        checkChangeOfSign(f_, a_, b_);
    }

    // setters
    void setA(T::VariableType a) { a_ = a; };
    void setB(T::VariableType b) { b_ = b; };
    void setAbsoluteTollerance(double tola) { tola_ = tola; };

    // methods
    T::VariableType solve() override;
};

class BrentSearch : public SolverBase
{
private:
    T::VariableType a_;
    T::VariableType b_;
    unsigned int maxIter_;

public:
    // constructors
    BrentSearch() = default;
    BrentSearch(const T::FunctionType &f,
                T::VariableType x1,
                double tol = 1e-4,
                unsigned int maxIter = 150) : SolverBase(f, tol), maxIter_(maxIter)
    {
        searchBracketInterval(f_, x1, a_, b_);
    }
    BrentSearch(const T::FunctionType &f, std::array<T::VariableType, 2> interval, double tol = 1e-4, unsigned int maxIter = 150)
        : SolverBase(f, tol), a_(interval[0]), b_(interval[1]), maxIter_(maxIter)
    {
        checkChangeOfSign(f_, a_, b_);
    }

    // setters
    void setA(T::VariableType a) { a_ = a; };
    void setB(T::VariableType b) { b_ = b; };
    void setMaxIter(unsigned int maxIter) { maxIter_ = maxIter; };

    // methods
    T::VariableType solve() override;
};

#endif // __SOLVERS__