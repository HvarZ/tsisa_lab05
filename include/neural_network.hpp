//
// Created by Захар on 22.11.2020.
//

#ifndef TSISA_LAB05_NEURAL_NETWORK_HPP
#define TSISA_LAB05_NEURAL_NETWORK_HPP

#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include <utility>
#include <algorithm>

using std::cout;
using std::endl;

class neuron {
private:
    double x;
    double y;

public:
    neuron() = default;

    void set_x(double buf_x) {
        x = buf_x;
    }

    void set_y(double buf_y) {
        y = buf_y;
    }

    [[nodiscard]] auto get_x() const noexcept -> double {
        return x;
    }

    [[nodiscard]] auto get_y() const noexcept -> double {
        return y;
    }

    auto operator<(neuron& neuron1) const -> bool {
        return y < neuron1.y;
    }

    auto operator==(neuron& neuron1) const -> bool {
        return y == neuron1.y && x == neuron1.x;
    }

    neuron(neuron& neuron1) {
        x = neuron1.x;
        y = neuron1.y;
    }

    neuron& operator=(const neuron& neuron1) = default;

};

auto random(const double a, const double b) -> double {
    if (a > b) throw std::invalid_argument("Invalid segment");
    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_real_distribution<double> rand(a, b);
    return rand(rng);
}

auto linear_function(double c, double d, double x) -> double {
    return  c * x + d;
}

auto random_error(double a, double b, double A) -> double {
    return A * random(a, b);
}

auto fill_network(double c, double d, double A ,double a, double b, size_t numbers_neurons) -> std::vector<neuron> {
    auto neuron_distance = (b - a) / static_cast<double>(numbers_neurons + 1);
    std::vector<neuron> neurons(numbers_neurons);
    auto current_x = a;
    for (auto& neuron : neurons) {
        current_x += neuron_distance;
        neuron.set_x(current_x);
        neuron.set_y(linear_function(c, d, neuron.get_x()) + random_error(-0.5, 0.5, A));
    }
    return neurons;
}


auto sum_x(const std::vector<neuron>& neurons) -> double {
    auto sum = 0.0;
    for (const auto& _neuron : neurons) {
        sum += _neuron.get_x();
    }
    return sum;
}

auto sum_y(const std::vector<neuron>& neurons) -> double {
    auto sum = 0.0;
    for (const auto& _neuron : neurons) {
        sum += _neuron.get_y();
    }
    return sum;
}

auto sum_square_x(const std::vector<neuron>& neurons) -> double {
    auto sum = 0.0;
    for (const auto& _neuron : neurons) {
        sum += std::pow(_neuron.get_x(), 2);
    }
    return sum;
}

auto sum_xy(const std::vector<neuron>& neurons) -> double {
    auto sum = 0.0;
    for (const auto& _neuron : neurons) {
        sum += (_neuron.get_x() * _neuron.get_y());
    }
    return sum;
}

auto result(const std::vector<neuron>& neurons) -> std::pair<double, double> { // MNK
    double w0, w1;
    w1 = (sum_x(neurons) * sum_y(neurons) - neurons.size() * sum_xy(neurons))
         / (std::pow(sum_x(neurons), 2) - neurons.size() * sum_square_x(neurons));
    w0 = (sum_y(neurons) - w1 * sum_x(neurons)) / neurons.size();
    return std::make_pair(w0, w1);
}

[[maybe_unused]] void print(const std::vector<neuron>& neurons){
    for(const auto& neuron : neurons) {
        std::cout << "x: " << neuron.get_x() << " | " << "y: " << neuron.get_y() << std::endl;
    }
}



#endif //TSISA_LAB05_NEURAL_NETWORK_HPP
