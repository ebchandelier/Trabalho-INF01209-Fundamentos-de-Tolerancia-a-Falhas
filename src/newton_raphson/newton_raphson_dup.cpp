#include "newton_raphson.hpp"

#include <fstream>
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>


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


void run(std::vector<double>& results)
{
    for(double x0 = -4.0; x0 <= 4.0; x0 += 0.0001)
    {
        double result = newton_raphson(rastrigin_function<double>, x0,
                                       finite_central_diff,
                                       1000, 1e-14, 1e-15);
        results.push_back(result);
    }
}


int main()
{
    // Uses two threads to duplicate.
    std::vector<double> results1;
    results1.reserve(80000);
    std::vector<double> results2;
    results2.reserve(80000);

    /*
    std::thread th1(run, std::ref(results1));
    std::thread th2(run, std::ref(results2));
    th1.join();
    th2.join();
    */

    run(results1);
    run(results2);

    // SDC detection.
    if(results1 != results2)
    {
        std::ofstream detectedStream;
        detectedStream.open("/tmp/newton_raphson/detected.log");
        detectedStream << "results1.size();results2.size()\n"
                       << results1.size() << ";" << results2.size() << "\n\n";

        detectedStream << "i;results1[i];results2[i]\n";
        unsigned int size = std::min(results1.size(), results2.size());
        for(unsigned int i = 0; i < size; ++i)
        {
            if(results1 != results2)
            {
                detectedStream << i << ";" << results1[i] << ";"
                               << results2[i] << "\n";
            }
        }

        detectedStream.close();
    }

    // Writes outputs.
    std::ofstream outFile1;
    outFile1.open("/tmp/newton_raphson/output.txt");
    for(double value : results1)
    {
        outFile1 << value << "\n";
    }
    outFile1.close();

    return 0;
}
