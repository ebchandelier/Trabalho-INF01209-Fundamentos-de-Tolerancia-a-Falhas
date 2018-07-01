#include "newton_raphson_hardned.hpp"

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


int main()
{
    std::ofstream outFile;
    outFile.open("/tmp/newton_raphson/output.txt");

    for(double x0 = -4.0; x0 <= 4.0; x0 += 0.0001)
    {
        double result = newton_raphson(rastrigin_function<double>, x0,
                                       finite_central_diff,
                                       1000, 1e-14, 1e-15,
                                       std::sqrt(machine_eps<double>()));
        outFile << result << "\n";
    }

    return 0;
}
