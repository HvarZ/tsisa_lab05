#include "include/neural_network.hpp"

int main () {
    // Variant 15
    const double a = -5;
    const double b = 0;
    const double c = 0.1;
    const double d = 2;
    const size_t N = 32;
    const double A = 0.2;

    auto network = fill_network(c, d, A, a, b, N); // заполнение нейронной сети

    auto w_result = result(network); // нахождение весовых коеффициентов

    print(network); // печать значений

    std::cout << "=======================Result=======================" << std::endl;
    std::cout << "w1 = " << w_result.second << " | " << "w0 = " << w_result.first << std::endl;

    return 0;
}