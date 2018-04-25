#include "newton_raphson.hpp"

#include <fstream>
// #include <chrono>
// #include <thread>

// Test functions.

template<typename TFloat>
TFloat rastrigin_function(TFloat x)
{
    const TFloat A  = 10.0;
    const TFloat PI = std::acos(-1.0);
    return A + x * x - A * std::cos(2.0 * PI * x);
}


template<typename TFloat>
TFloat test_func(TFloat x)
{
    return x * x -2.0;
}


int main(__attribute__((unused)) int argc, char** argv)
{
    std::ofstream outFile;
    outFile.open(std::string(argv[1]));

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    for(double x0 = -4.0; x0 <= 4.0; x0 += 0.0001)
    {
        double result = newton_raphson(rastrigin_function<double>, x0,
                                       finite_central_diff,
                                       1000, 1e-14, 1e-15);
        outFile << result << "\n";
    }

    return 0;
}
