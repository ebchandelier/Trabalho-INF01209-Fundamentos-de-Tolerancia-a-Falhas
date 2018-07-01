#ifndef GUARD_NEWTON_RAPHSON_HARDNED_HPP
#define GUARD_NEWTON_RAPHSON_HARDNED_HPP

#include <cmath>
#include <vector>
#include <limits>
#include <iostream>
#include <fstream>


template<typename T>
void check_for_SDC(const T& a, const T& b)
{
    if(a != b)
    {
        std::ofstream detectedStream;
        detectedStream.open("/tmp/newton_raphson/detected.log");
        detectedStream.close();
    }
}


template<typename TFloat>
TFloat machine_eps()
{
    return std::numeric_limits<TFloat>::epsilon();
}


// Typedef for finite difference functions.
template<typename TFloat, typename TFunc>
using FiniteDiff = TFloat (*)(TFunc f, TFloat x, TFloat h,
                              TFunc f_copy, TFloat x_copy, TFloat h_copy);


template<typename TFloat, typename TFunc>
TFloat finite_backward_diff(
    TFunc f,
    TFloat x,
    TFloat h,
    TFunc f_copy,
    TFloat x_copy,
    TFloat h_copy)
{
    check_for_SDC(f, f_copy);
    check_for_SDC(x, x_copy);
    check_for_SDC(h, h_copy);
    return f(x - h) / h;
}


template<typename TFloat, typename TFunc>
TFloat finite_central_diff(
    TFunc f,  // DUP
    TFloat x,  // DUP
    TFloat h,
    TFunc f_copy,
    TFloat x_copy,
    TFloat h_copy)
{
    check_for_SDC(f, f_copy);
    check_for_SDC(x, x_copy);
    check_for_SDC(h, h_copy);
    return (f(x + h) - f(x - h)) / (2.0 * h);
}


// Newton-Raphson method.
template<typename TFloat, typename TFunc>
TFloat newton_raphson(TFunc f  /* DUP */, TFloat x0,
                      FiniteDiff<TFloat, TFunc> fDiff,  // DUP
                      unsigned int maxIter, TFloat eps /* DUP */, TFloat delta /* DUP */,
                      TFloat h=std::sqrt(machine_eps<TFloat>()),  // DUP
                      bool debug=false)
{
    TFloat x = x0;      // Initial estimative.
    TFloat x_copy = x0;
    check_for_SDC(x, x_copy);

    TFunc f_copy = f;
    check_for_SDC(f, f_copy);

    TFloat h_copy = h;
    check_for_SDC(h, h_copy);

    TFloat f_x = f(x);  // Evaluates function at initial x.  // DUP

    bool df_x_too_small = false;
    bool found_root = false;
    unsigned int currIter = 0;

    bool df_x_too_small_copy = false;
    bool found_root_copy = false;
    unsigned int currIter_copy = 0;

    while(!df_x_too_small && !found_root && (currIter < maxIter))
    {
        // Derivative at current x.
        TFloat df_x = fDiff(f, x, h, f_copy, x_copy, h_copy);

        if(std::abs(df_x) < std::sqrt(machine_eps<TFloat>()))
        {
            // Derivative is too small.
            df_x_too_small = true;
            df_x_too_small_copy = true;
        }
        else
        {
            TFloat prev_x = x;  // Saves previous x value.
            check_for_SDC(prev_x, x);
            check_for_SDC(prev_x, x_copy);

            if(debug)
            {
                std::cout << "x     = " << x << "\n"
                          << "f(x)  = " << f_x << "\n"
                          << "f'(x) = " << df_x << "\n\n";
            }

            x = x - (f_x / df_x);   // Updates the estimative of x.
            x_copy = x_copy - (f_x / df_x);
            check_for_SDC(x, x_copy);

            f_x = f(x);             // Value of the function at the new x.

            if(std::abs(f_x) < eps)
            {
                // Achieved desired precision.
                found_root = true;
                found_root_copy = true;
            }
            else if(std::abs(x - prev_x) < delta)
            {
                // Root between x and prev_x.
                found_root = true;
                found_root_copy = true;
            }
        }

        ++currIter;
        ++currIter_copy;

        check_for_SDC(df_x_too_small, df_x_too_small_copy);
        check_for_SDC(found_root, found_root_copy);
        check_for_SDC(currIter, currIter_copy);
    }

    return x;
}


#endif  // GUARD_NEWTON_RAPHSON_HARDNED_HPP
