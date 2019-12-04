//
// Created by kosie on 12/3/2019.
//

#include <cmath>
#include <functional>

#include "gaussian_mutation.h"

gaussian_mutation::gaussian_mutation(gaussian_mutation_metadata *metadata, stochastic* stochastic_instance) {
    _height = metadata->height;
    _mean = metadata->mean;
    _variance = metadata->variance;

    _stochastic_instance = stochastic_instance;
}

gaussian_mutation::~gaussian_mutation() = default;

// parametric gaussian implementation
typedef std::function<double (double)> gaussian_t;
gaussian_t gaussian(double height, double mean, double variance) {
    return [height, mean, variance](double x) {
        double scalar = 1 / sqrt(2 * M_PI * variance);
        double exponent = -pow(x - mean, 2) / (2 * variance);
        return height * scalar * exp(exponent);
    };
}

chromosome *gaussian_mutation::invoke(vector_chromosome *chromosome) {
    double* seed = new double[chromosome->_size];
    size_t index = _stochastic_instance->rand_int(chromosome->_size);

    double x = _stochastic_instance->rand_double(); // TODO: how do we determine the bounds on this?
    gaussian_t g = gaussian(_height, _mean, _variance);

    for(size_t i = 0; i < chromosome->_size; i++)
        seed[i] = chromosome->get_gene(i);
    seed[index] += g(x);

    // TODO: this information flow needs to be reworked. are we holding onto metadata?
    vector_chromosome* child = new vector_chromosome(nullptr, seed);
    return child;
}