/*
    Simulate a thrown ball with air resistance and optimize the angle of the throw to hit a specific target coordinate.
*/

#include <cstdio>
#include <iostream>
#include <algorithm>

#include "numerical.h"

using namespace numerical;

typedef NVector<double, 4> Vector;

double target_x = 450.0;
double target_y = 20.0;
double gravity_constant = 9.81;
double air_resistance = 0.20;
double start_velocity = 150.0;

Vector gravity(double time, Vector y) {
    Vector dydt;
    dydt[0] = y[2];
    dydt[1] = y[3];
    dydt[2] = -air_resistance * y[2];
    dydt[3] = -gravity_constant - air_resistance * y[2];

    return dydt;
}

double min_distance(std::vector<Vector> y) {
    std::vector<double> min_vals(y.size());
    auto distance = [](Vector y) -> double {
        return std::pow(y[0] - target_x, 2) + std::pow(y[1] - target_y, 2);
    };
    std::transform(y.begin(), y.end(), min_vals.begin(), distance);

    return *std::min_element(min_vals.begin(), min_vals.end());
}

double simulate_trajectory(double angle) {
    Vector y_start = {0.0, 0.0, start_velocity * std::sin(angle), start_velocity * std::cos(angle)};
    ode::RungeKutta solver;
    solver.dense_output = true;
    auto result = solver.run(gravity, y_start, 0.0, 10.0, 1e-4);
    
    return min_distance(result.dense_y);
}

int main() {
    auto result_angle = optimize::brent(simulate_trajectory, 0.0, constants::pi_double / 2.0, 1e-4, 1000);
    fprintf(stderr, "angle / deg: %f\n", result_angle.x * 180 / 3.14);
    fprintf(stderr, "f(angle):    %f\n", result_angle.fx);
    fprintf(stderr, "iterations:  %u\n", result_angle.iterations);

    Vector y_start = {0.0, 0.0, start_velocity * std::sin(result_angle.x), start_velocity * std::cos(result_angle.x)};
    ode::RungeKutta solver;
    solver.dense_output = true;
    auto result_ode = solver.run(gravity, y_start, 0.0, 10.0, 1e-1);
    result_ode.display_dense_output();

    return 0;
}