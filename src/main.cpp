#include <iostream>
#include <iomanip>

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

    std::array<SolverTraits::VariableType, 2> interval{-1., 0.};

    std::cout << std::endl;
    std::cout << "###########" << std::endl;
    std::cout << "# Solvers #" << std::endl;
    std::cout << "###########" << std::endl;
    std::cout << std::endl;

    std::cout << "Function: 0.5 - exp{pi*x}" << std::endl;
    std::cout << "Expected zero: " << std::log(0.5) / M_PI << std::endl;
    std::cout << std::endl;

    // Secant
    auto solver1 = SolverFactory<Secant>(f, interval);
    auto result1 = SafeSolve(solver1);
    std::cout << std::setw(15) << std::left << "- Secant: " << result1 << std::endl;

    // Bisection
    auto solver2 = SolverFactory<Bisection>(f, interval);
    auto result2 = SafeSolve(solver2);
    std::cout << std::setw(15) << std::left << "- Bisection: " << result2 << std::endl;

    // Newton
    auto solver3 = SolverFactory<Newton>(f, df, -1.);
    auto result3 = SafeSolve(solver3);
    std::cout << std::setw(15) << std::left << "- Newton: " << result3 << std::endl;

    // QuasiNewton
    auto solver4 = SolverFactory<Newton>(f, df, -1.);
    auto result4 = SafeSolve(solver4);
    std::cout << std::setw(15) << std::left << "- QuasiNewton: " << result4 << std::endl;

    // RegulaFalsi
    auto solver5 = SolverFactory<RegulaFalsi>(f, interval);
    auto result5 = SafeSolve(solver5);
    std::cout << std::setw(15) << std::left << "- RegulaFalsi: " << result5 << std::endl;

    std::cout << std::endl;

    return 0;
}