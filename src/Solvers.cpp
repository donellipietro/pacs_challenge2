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
    double delta = b_ - a_;
    T::ReturnType yc{ya};
    T::VariableType c{a_};
    while (std::abs(delta) > 2 * tol_)
    {
        c = (a_ + b_) / 2.;
        yc = f_(c);
        if (yc * ya < 0.0)
        {
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

void checkChangeOfSign(const SolverTraits::FunctionType &f, SolverTraits::VariableType &a, SolverTraits::VariableType &b)
{
    if (f(a) * f(b) > 0)
    {
        std::cout << "Function must change sign at the two end values!" << std::endl;
        std::cout << std::endl;

        SolverTraits::VariableType new_a;
        SolverTraits::VariableType new_b;
        bool status;

        std::cout << "Trying to find an interval that brackets the zero of f starting from a" << std::endl;
        std::cout << std::endl;
        std::tie(new_a, new_b, status) = bracketInterval(f, a);

        if (!status)
        {
            std::cout << "Trying to find an interval that brackets the zero of f starting from b" << std::endl;
            std::cout << std::endl;
            std::tie(new_a, new_b, status) = bracketInterval(f, b);
        }

        if (!status)
        {
            throw std::invalid_argument("It was not possible to find an interval that brackets the zero of f");
        }

        std::cout << "Interval found! " << std::endl
                  << "Initial interval: a = " << a << ", b = " << b << std::endl
                  << "New interval: a = " << new_a << ", b = " << new_b << std::endl
                  << std::endl;
        a = new_a;
        b = new_b;
    }
}

/*
 * This function tries to find an interval that brackets the zero of a
 * function f. It does so by sampling the value of f at points
 * generated starting from a given point
 *
 * Parameters:
 * - f: The function.
 * - x1: initial point
 * - h_ initial increment for the sampling
 * - maxIter: maximum number of iterations
 *
 * Return:
 * It returns a tuple with the bracketing points and a bool which is true if number
 * of iterations not exceeded (bracket found)
 */
std::tuple<SolverTraits::VariableType, SolverTraits::VariableType, bool>
bracketInterval(const SolverTraits::FunctionType &f, SolverTraits::VariableType x1,
                double h, unsigned int maxIter)
{
    constexpr double expandFactor = 1.5;
    h = std::abs(h);
    auto direction = 1.0;
    SolverTraits::VariableType x2 = x1 + h;
    SolverTraits::ReturnType y1 = f(x1);
    SolverTraits::ReturnType y2 = f(x2);
    unsigned int iter = 0u;

    // get initial decrement direction
    while ((y1 * y2 > 0) && (iter < maxIter))
    {
        ++iter;
        if (std::abs(y2) > std::abs(y1))
        {
            std::swap(y1, y2);
            std::swap(x1, x2);
            // change direction
        }
        direction = (x2 > x1) ? 1.0 : -1.0;
        x1 = x2;
        y1 = y2;
        x2 += direction * h;
        y2 = f(x2);
        h *= expandFactor;
    }
    return std::make_tuple(x1, x2, iter < maxIter);
}