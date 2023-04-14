#include <iostream>

#include <cmath>
#include "SolverFactory.hpp"

int main(int argc, char **argv)
{

    SolverTraits::FunctionType f{
        [](const double x)
        { return 0.5 - std::exp(M_PI * x); }};
    SolverTraits::FunctionType df{
        [](const double x)
        { return -M_PI * std::exp(M_PI * x); }};

    auto solver1 = SolverFactory<Secant>(f, -1., 0);
    std::cout << solver1->solve() << std::endl;

    auto solver2 = SolverFactory<Bisection>(f, -1., 0.);
    std::cout << solver2->solve() << std::endl;

    auto solver3 = SolverFactory<Newton>(f, df, -1.);
    std::cout << solver3->solve() << std::endl;

    return 0;
}