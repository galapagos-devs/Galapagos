#ifndef _GALAPAGOS_H_
#define _GALAPAGOS_H_

#include <cstdint>

#include "galapagos_metadata.h"
#include "population.h"
#include "stochastic.h"

class galapagos_session {
public:
	stochastic* __stochastic__;

public:
	galapagos_session();
	~galapagos_session();

	static galapagos_session& get_instance();

	population_metadata* create_population_metadata();

	population* create_population(population_metadata* population_metadata);
};

#ifdef WIN32
#define GALAPAGOS_API extern "C" __declspec(dllexport)
#else
#define GALAPAGOS_API extern "C" __attribute__((visibility("default")))
#endif

GALAPAGOS_API population_metadata* create_population_metadata();

GALAPAGOS_API void set_population_metadata_size(population_metadata* population_metadata, size_t size);
GALAPAGOS_API size_t get_population_metadata_size(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_survival_rate(population_metadata* population_metadata, double survival_rate);
GALAPAGOS_API double get_population_metadata_survival_rate(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_distance_threshold(population_metadata* population_metadata, double distance_threshold);
GALAPAGOS_API double get_population_metadata_distance_threshold(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_cooperative_coevolution(population_metadata* population_metadata, bool cooperative_coevolution);
GALAPAGOS_API bool get_population_metadata_cooperative_coevolution(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_num_selection_algorithm_metadata(population_metadata* population_metadata, size_t num_selection_algorithm_metadata);
GALAPAGOS_API size_t get_population_metadata_num_selection_algorithm_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_selection_algorithm_metadata(population_metadata* population_metadata, selection_algorithm_metadata* selection_algorithm_metadata);
GALAPAGOS_API selection_algorithm_metadata* get_population_metadata_selection_algorithm_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_num_termination_condition_metadata(population_metadata* population_metadata, size_t num_termination_condition_metadata);
GALAPAGOS_API size_t get_population_metadata_num_termination_condition_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_termination_condition_metadata(population_metadata* population_metadata, termination_condition_metadata* termination_condition_metadata);
GALAPAGOS_API termination_condition_metadata* get_population_metadata_termination_condition_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_fitness_function(population_metadata* population_metadata, fitness_func_t fitness_function);
GALAPAGOS_API fitness_func_t get_population_metadata_fitness_function(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_num_chromosome_metadata(population_metadata* population_metadata, size_t num_chromosome_metadata);
GALAPAGOS_API size_t get_population_metadata_num_chromosome_metadata(population_metadata* population_metadata);

GALAPAGOS_API void set_population_metadata_chromosome_metadata(population_metadata* population_metadata, chromosome_metadata* chromosome_metadata);
GALAPAGOS_API chromosome_metadata* get_population_metadata_chromosome_metadata(population_metadata* population_metadata);

GALAPAGOS_API population* create_population(population_metadata* population_metadata);

#endif /* _GALAPAGOS_H_ */
