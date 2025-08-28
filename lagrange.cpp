#include "lagrange.hpp"
#include <vector>

double lagrange_interpolate(const std::vector<long long>& x, const std::vector<long long>& y, double xi) {
    int n = x.size();
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (xi - x[j]) / (double)(x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}
