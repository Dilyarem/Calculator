#include <climits>
#include <stdexcept>

void CheckSumForOverflowing(int a, int b) {
    if ((b > 0) && ((INT_MAX - b) < a)) {
        throw std::overflow_error("Integer overflow in sum");
    }
    if ((b < 0) && ((INT_MIN - b) > a)) {
        throw std::underflow_error("Integer underflow in sum");
    }
}

void CheckProdForOverflowing(int a, int b) {
    if (((a > 0 && b > 0) || (a < 0 && b < 0)) && ((INT_MAX / std::abs(b)) < std::abs(a))) {
        throw std::overflow_error("Integer overflow in production");
    }
    if (((a > 0 && b < 0) || (a < 0 && b > 0))  && ((INT_MIN / std::abs(b)) > -std::abs(a))) {
        throw std::underflow_error("Integer underflow in production");
    }
}