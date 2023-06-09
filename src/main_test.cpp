#include <iostream>
#include <cmath>

#include "Solvers.hpp"
#include "basicZeroFun.hpp"
#include "SolverFactory.hpp"

int main(int argc, char **argv)
{

    SolverTraits::FunctionType f{
        [](const double x)
        { return 0.5 - std::exp(M_PI * x); }};
    SolverTraits::FunctionType df{
        [](const double x)
        { return -M_PI * std::exp(M_PI * x); }};

    SolverTraits::FunctionType f1{
        [](const double x)
        { return x * x; }};
    SolverTraits::FunctionType df1{
        [](const double x)
        { return 2 * x; }};

    // Secant
    std::cout << std::endl;
    std::cout << "##################" << std::endl;
    std::cout << "# Test 1: Secant #" << std::endl;
    std::cout << "##################" << std::endl;
    std::cout << std::endl;

    Secant solver1(f, std::array<SolverTraits::VariableType, 2>{-1, 0}, 1e-4, 1e-10, 150);
    auto [result1, status1] = apsc::secant<SolverTraits::FunctionType>(f, -1, 0);

    std::cout << "- basiZeroFun: " << result1 << std::endl;
    std::cout << "- SolverBase:  " << solver1.solve() << std::endl;
    std::cout << std::endl;

    // Bisection
    std::cout << std::endl;
    std::cout << "#####################" << std::endl;
    std::cout << "# Test 2: Bisection #" << std::endl;
    std::cout << "#####################" << std::endl;
    std::cout << std::endl;

    Bisection solver2(f, std::array<SolverTraits::VariableType, 2>{-1, 0}, 1.e-5);
    auto result2 = apsc::bisection<SolverTraits::FunctionType>(f, -1, 0);

    std::cout << "- basiZeroFun: " << result2 << std::endl;
    std::cout << "- SolverBase:  " << solver2.solve() << std::endl;
    std::cout << std::endl;

    // RegulaFalsi
    std::cout << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << "# Test 2.1: RegulaFalsi #" << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << std::endl;

    RegulaFalsi solver2_1(f, std::array<SolverTraits::VariableType, 2>{-1, 0}, 1.e-5, 1.e-10);
    auto result2_1 = apsc::regulaFalsi<SolverTraits::FunctionType>(f, -1, 0, 1.e-5, 1.e-10);

    std::cout << "- basiZeroFun: " << result2_1 << std::endl;
    std::cout << "- SolverBase:  " << solver2_1.solve() << std::endl;
    std::cout << std::endl;

    // BrentSearch
    std::cout << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << "# Test 2.2: BrentSearch #" << std::endl;
    std::cout << "#########################" << std::endl;
    std::cout << std::endl;

    BrentSearch solver2_2(f, std::array<SolverTraits::VariableType, 2>{-1, 0}, 1.e-5);
    auto [result2_2, status2_2] = apsc::brent_search<SolverTraits::FunctionType>(f, -1, 0, 1.e-5);

    std::cout << "- basiZeroFun: " << result2_2 << std::endl;
    std::cout << "- SolverBase:  " << solver2_2.solve() << std::endl;
    std::cout << std::endl;

    // Newton
    std::cout << std::endl;
    std::cout << "##################" << std::endl;
    std::cout << "# Test 3: Newton #" << std::endl;
    std::cout << "##################" << std::endl;
    std::cout << std::endl;

    Newton solver3(f, df, -0.5, 1e-4, 1e-10, 150);
    auto [result3, status3] = apsc::Newton<SolverTraits::FunctionType>(f, df, -0.5);

    std::cout << "- basiZeroFun: " << result3 << std::endl;
    std::cout << "- SolverBase:  " << solver3.solve() << std::endl;
    std::cout << std::endl;

    // Bisection
    std::cout << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << "# Test 4: Bisection + interval search #" << std::endl;
    std::cout << "#######################################" << std::endl;
    std::cout << std::endl;

    Bisection solver4(f, std::array<SolverTraits::VariableType, 2>{-5, -1}, 1.e-5);

    std::cout << "Zero: " << solver4.solve() << std::endl;
    std::cout << std::endl;

    // Bisection
    std::cout << std::endl;
    std::cout << "########################################" << std::endl;
    std::cout << "# Test 5: Bisection + switch to secant #" << std::endl;
    std::cout << "########################################" << std::endl;
    std::cout << std::endl;

    // By using the constructor
    // -> The user has to handle the exception by himself
    std::cout << "Constructor:" << std::endl;
    std::cout << std::endl;
    try
    {
        Bisection solver5(f1, std::array<SolverTraits::VariableType, 2>{-1, 0.3}, 1.e-5);
        std::cout << "Zero: " << solver5.solve() << std::endl;
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
    }

    // By using the factory
    // -> The factory catches the possible exception and tries
    //    to solve the problem with a different solver
    std::cout << "Factory:" << std::endl;
    std::cout << std::endl;
    auto solver5 = SolverFactory<Bisection>(f1, std::array<SolverTraits::VariableType, 2>{-1, 0.3}, 1.e-5);
    auto result5 = SafeSolve(solver5);
    std::cout << "Zero: " << result5 << std::endl;
    std::cout << std::endl;

    // Bisection
    std::cout << std::endl;
    std::cout << "########################################################" << std::endl;
    std::cout << "# Test 5bis: Bisection when only one point is provided #" << std::endl;
    std::cout << "########################################################" << std::endl;
    std::cout << std::endl;

    std::cout << "An interval exists:" << std::endl;
    std::cout << std::endl;

    Bisection solver5bis1(f, -5, 1.e-5);

    std::cout << "Zero: " << solver5bis1.solve() << std::endl;
    std::cout << std::endl;

    std::cout << "An interval does not exist, constructor:" << std::endl;
    std::cout << std::endl;

    try
    {
        Bisection solver5bis2(f1, -1, 1.e-5);

        std::cout << "Zero: " << solver5bis2.solve() << std::endl;
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
    }

    std::cout << "An interval does not exist, factory:" << std::endl;
    std::cout << std::endl;

    auto solver5bis3 = SolverFactory<Bisection>(f1, -1, 1.e-5);
    auto result5bis3 = SafeSolve(solver5bis3);
    std::cout << "Zero: " << result5bis3 << std::endl;
    std::cout << std::endl;

    // QuasiNewton
    std::cout << std::endl;
    std::cout << "#######################" << std::endl;
    std::cout << "# Test 6: QuasiNewton #" << std::endl;
    std::cout << "#######################" << std::endl;
    std::cout << std::endl;

    Newton solver6_N(f1, df1, -0.5, 1e-4, 1e-10, 150);
    QuasiNewton solver6_QN(f1, -0.5, 1e-4, 1e-10, 150);

    std::cout << "- Newton: " << solver6_N.solve() << std::endl;
    std::cout << "- QuasiNewton: " << solver6_QN.solve() << std::endl;
    std::cout << std::endl;

    // Newton -> QuasiNewton
    std::cout << std::endl;
    std::cout << "######################################" << std::endl;
    std::cout << "# Test 7: From Newton to QuasiNewton #" << std::endl;
    std::cout << "######################################" << std::endl;
    std::cout << std::endl;

    // Constructor
    std::cout << "Constructor:" << std::endl;
    std::cout << std::endl;
    try
    {
        Newton solver7(f, -0.5, 1e-4, 1e-10, 150);
        std::cout << "Zero: " << solver7.solve() << std::endl;
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cout << std::endl;
    }

    // Factory
    std::cout << "Factory:" << std::endl;
    std::cout << std::endl;
    auto solver7 = SolverFactory<Newton>(f, -0.5, 1e-4, 1e-10, 150);
    auto result7 = SafeSolve(solver7);
    std::cout << "Zero: " << result7 << std::endl;
    std::cout << std::endl;

    // Safe solve
    std::cout << std::endl;
    std::cout << "#####################" << std::endl;
    std::cout << "# Test 8: SafeSolve #" << std::endl;
    std::cout << "#####################" << std::endl;
    std::cout << std::endl;

    auto solver8 = SolverFactory<Secant>(f1, std::array<SolverTraits::VariableType, 2>{-1, 1}, 1.e-5);
    auto result8 = SafeSolve(solver8);
    std::cout << "Zero: " << result8 << std::endl;
    std::cout << std::endl;

    return 0;
}