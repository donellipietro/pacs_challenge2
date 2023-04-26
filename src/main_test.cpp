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

    Secant solver1(f, -1, 0, 1e-4, 1e-10, 150);
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

    Bisection solver2(f, -1, 0, 1.e-5);
    auto result2 = apsc::bisection<SolverTraits::FunctionType>(f, -1, 0);

    std::cout << "- basiZeroFun: " << result2 << std::endl;
    std::cout << "- SolverBase:  " << solver2.solve() << std::endl;
    std::cout << std::endl;

    // Newton
    std::cout << std::endl;
    std::cout << "##################" << std::endl;
    std::cout << "# Test 2: Newton #" << std::endl;
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

    Bisection solver4(f, -5, -1, 1.e-5);

    std::cout << "Zero:  " << solver4.solve() << std::endl;
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
        Bisection solver5(f1, -1, 1, 1.e-5);
        std::cout << "Zero:  " << solver5.solve() << std::endl;
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
    auto solver5 = SolverFactory<Bisection>(f1, -1, 1, 1.e-5);
    std::cout << "Zero:  " << solver5->solve() << std::endl;
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
    std::cout << "- QuasiNewton:  " << solver6_QN.solve() << std::endl;
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
        std::cout << "Zero:  " << solver7.solve() << std::endl;
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
    std::cout << "Zero:  " << solver7->solve() << std::endl;
    std::cout << std::endl;

    return 0;
}