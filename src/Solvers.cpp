#include "Solvers.hpp"

// Secant solve method
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
        double den = (yb - ya);
        if (den == 0)
            throw std::invalid_argument("Division by zero detected, method stopped.");
        c = a_ - ya * (b_ - a_) / den;
        double yc = f_(c);
        resid = std::abs(yc);
        goOn = resid > check;
        ya = yc;
        a_ = c;
    }

    if (iter == maxIter_)
    {
        throw std::invalid_argument("The maximum number of iterations has been reached without convergence!");
    }

    return c;
};

// Bisection solve method
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

// Newton solve method
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
        auto dfa = df_(a);
        if (dfa == 0)
            throw std::invalid_argument("Division by zero detected, method stopped.");
        a += -ya / dfa;
        ya = f_(a);
        resid = std::abs(ya);
        goOn = resid > check;
    }

    if (iter == maxIter_)
    {
        throw std::invalid_argument("The maximum number of iterations has been reached without convergence!");
    }

    return a;
};

/* This function checks that the evaluations of the function at the two ends of the provided interval have opposite sign.
 * If this is not the case the function tries to find a valid interval by calling the function bracketInterval.
 * In the worst case an exception is thrown.
 */
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

/* This function searches a valid interval given an initial point.
 * In the worst case an exception is thrown.
 */
void searchBracketInterval(const SolverTraits::FunctionType &f,
                           SolverTraits::VariableType x1, SolverTraits::VariableType &a, SolverTraits::VariableType &b)
{
    std::cout << "Trying to find an interval that brackets the zero of f starting from the provided point" << std::endl;
    std::cout << std::endl;
    auto [new_a, new_b, status] = bracketInterval(f, x1);
    if (status)
    {
        std::cout << "Interval found! " << std::endl
                  << "Initial point: x1 = " << x1 << std::endl
                  << "New interval: a = " << new_a << ", b = " << new_b << std::endl
                  << std::endl;
        a = new_a;
        b = new_b;
    }
    else
    {
        throw std::invalid_argument("It was not possible to find an interval that brackets the zero of f");
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

// Approximates the first derivative of a function with centered finite differences
double
finiteDiff(const SolverTraits::FunctionType &f, const SolverTraits::VariableType x, const double h)
{
    return (f(x + h) - f(x - h)) / (2 * h);
}