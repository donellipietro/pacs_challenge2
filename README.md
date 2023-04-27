# Challenge 2 - Build a hierarchy of solvers for f(x) = 0

This code was developed for the course of **Advanced Programming for Scientific Computing** for the MSc. in Mathematical Engineering at Politecnico di Milano, A.Y. 2022/2023.

## Problem

It is of interest to implement a hierarchy of solvers for numerically find the zero of a given function.

## Description

```
.
|-- README.md
|-- doc
|   `-- Challenge21-22_2.pdf
`-- src
    |-- Makefile
    |-- SolverBase.hpp
    |-- SolverFactory.hpp
    |-- SolverTraits.hpp
    |-- Solvers.cpp
    |-- Solvers.hpp
    |-- include
    |-- lib
    |-- main.cpp
    `-- main_test.cpp
```

-   [`SolverTraits.hpp`](src/SolverTraits.hpp)
    It collects the main types used by all classes, to allow more flexibility and readability.

    -   `ScalarType: double`
    -   `VariableType: double`
    -   `ReturnType: double`
    -   `FunctionType: std::function<ReturnType(const VariableType &)>`

-   [`SolverBase.hpp`](src/SolverBase.hpp)
    This is an interface that constitutes the base for all the solvers. It exposes the pure virtual method solve() that takes no argument and return the results. A basic solver is characterized by the function whose zero is to be found and the tolerance that the numerical solution must satisfy.

-   [`Solvers.hpp`](src/Solvers.hpp)
    Solvers are public inheritance of SolverBase and they implement the associated `Solve()` method. The solvers here implemented are:

    -   `Secant`
    -   `Bisection`
    -   `RegulaFalsi`
    -   `BrentSearch`
    -   `Newton`
    -   `QuasiNewton`

    In particular `QuasiNewton` is a special implementation of `Newton` method in which the derivative of the function is computed through centered finite differences.
    Methods are implemented in [`Solvers.cpp`](src/Solvers.cpp).

-   [`SolverFactory.hpp`](src/SolverFactory.hpp)
    This is a factory of solvers that handles bad initilaization of the solver by calling a more suitable solver given the available data. Using the factory to initialize a solver allows automatic handling of the exceptions that are generated if the solver is misinitialized. In particular, when available, the factory proposes an alternate solver compatible with the initialization provided.
    It is also implemented the function `SafeSolve()` that calls the method `solve()` of the object passed by reference, exploting dynamic bindig, and it handles the possible exception due to the execution of that method.

-   [`main.cpp`](src/main.hpp) solves the problem of interest with all the implemented solvers.

-   [`main_test.cpp`](src/main_test.hpp) performs tests on all the implemented features.

## How to use it

Before compiling the code you must save in an environment variable called `MY_PACS_ROOT` the directory where the course examples are contained (e.g. `/home/jellyfish/shared-folder/pacs-examples/Examples`). This is used to include the `basicZeroFun` library that is used in `main_test.cpp` to check that the implemented methods provide the same results.

The `Makefile` file implements all the commands needed to compile and use the code. In particular, the following targets are available:

-   `make` compiles the code and generates the executables.
-   `make run` compiles the code and launch the main.
-   `make test` compiles the code and launches the test.

## Author

Pietro Donelli ([@donellipietro](https://github.com/donellipietro))
