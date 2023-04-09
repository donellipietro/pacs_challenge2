#include "Solvers.hpp"

SolverTraits::VariableType Secant::solve()
{
    T::ReturnType ya = f_(a_);
    double resid = std::abs(ya);
    T::VariableType c{a_};
    unsigned int iter{0u};
    double check = tol_ * resid + tola_;
    bool goOn = resid > check;
    while (goOn && iter < maxIter_)
    {
        ++iter;
        double yb = f_(b_);
        c = a_ - ya * (b_ - a_) / (yb - ya);
        double yc = f_(c);
        resid = std::abs(yc);
        goOn = resid > check;
        ya = yc;
        a_ = c;
    }

    return c;
};

SolverTraits::VariableType Bisection::solve()
{
    T::ReturnType ya = f_(a_);
    T::ReturnType yb = f_(b_);
    double delta = b_ - a_;
    if (ya * yb > 0)
        std::cerr << "Function must change sign at the two end values" << std::endl;
    T::ReturnType yc{ya};
    T::VariableType c{a_};
    while (std::abs(delta) > 2 * tol_)
    {
        c = (a_ + b_) / 2.;
        yc = f_(c);
        if (yc * ya < 0.0)
        {
            yb = yc;
            b_ = c;
        }
        else
        {
            ya = yc;
            a_ = c;
        }
        delta = b_ - a_;
    }
    return (a_ + b_) / 2.;
};

SolverTraits::VariableType Newton::solve()
{

    T::VariableType a{x0_};

    T::ReturnType ya = f_(a);
    double resid = std::abs(ya);
    unsigned int iter{0u};
    double check = tol_ * resid + tola_;
    bool goOn = resid > check;
    while (goOn && iter < maxIter_)
    {
        ++iter;
        a += -ya / df_(a);
        ya = f_(a);
        resid = std::abs(ya);
        goOn = resid > check;
    }

    return a;
};
