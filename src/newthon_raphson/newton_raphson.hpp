#ifndef GUARD_NEWTON_RAPHSON_HPP
#define GUARD_NEWTON_RAPHSON_HPP

#include <cmath>
#include <vector>
#include <limits>
#include <iostream>


template<typename TFloat>
TFloat machine_eps()
{
    return std::numeric_limits<TFloat>::epsilon();
}


// Typedef for finite difference functions.
template<typename TFloat, typename TFunc>
using FiniteDiff = TFloat (*)(TFunc f, TFloat x, TFloat h);


template<typename TFloat, typename TFunc>
TFloat finite_backward_diff(
    TFunc f,
    TFloat x,
    TFloat h=std::sqrt(machine_eps<TFloat>()))
{
    return f(x - h) / h;
}


template<typename TFloat, typename TFunc>
TFloat finite_central_diff(
    TFunc f,
    TFloat x,
    TFloat h=std::sqrt(machine_eps<TFloat>()))
{
    return (f(x + h) - f(x - h)) / (2.0 * h);
}


// Newton-Raphson method.
template<typename TFloat, typename TFunc>
TFloat newton_raphson(TFunc f, TFloat x0,
                      FiniteDiff<TFloat, TFunc> fDiff,
                      unsigned int maxIter, TFloat eps, TFloat delta,
                      TFloat h=std::sqrt(machine_eps<TFloat>()),
                      bool debug=false)
{
    TFloat x = x0;      // Initial estimative.
    TFloat f_x = f(x);  // Evaluates function at initial x.

    bool df_x_too_small = false;
    bool found_root = false;
    unsigned int currIter = 0;
    while(!df_x_too_small && !found_root && (currIter < maxIter))
    {
        TFloat df_x = fDiff(f, x, h);  // Derivative at current x.

        if(std::abs(df_x) < std::sqrt(machine_eps<TFloat>()))
        {
            // Derivative is too small.
            df_x_too_small = true;
            x = std::numeric_limits<TFloat>::signaling_NaN();
        }
        else
        {
            TFloat prev_x = x;      // Saves previous x value.

            if(debug)
            {
                std::cout << "x     = " << x << "\n"
                          << "f(x)  = " << f_x << "\n"
                          << "f'(x) = " << df_x << "\n\n";
            }

            x = x - (f_x / df_x);   // Updates the estimative of x.
            f_x = f(x);             // Value of the function at the new x.

            if(std::abs(f_x) < eps)
            {
                // Achieved desired precision.
                found_root = true;
            }
            else if(std::abs(x - prev_x) < delta)
            {
                // Root between x and prev_x.
                found_root = true;
            }
        }

        ++currIter;
    }

    return x;
}


#endif  // GUARD_NEWTON_RAPHSON_HPP
