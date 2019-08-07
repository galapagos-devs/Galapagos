#include "../API/Factory/genetic_factory.h"

#include <vector>

#include "../../Source/population.cpp"
#include "../API/population.h"

population* genetic_factory::create_population(population_metadata* population_metadata)
{
	population_internal* population_obj = new population_internal(population_metadata);
	population *population_ptr = (population*)population_obj;
	return population_ptr;
}

selection_algorithm* genetic_factory::create_selection_algorithm(population_metadata* population_metadata)
{
	return nullptr;
}

std::vector<termination_condition*> genetic_factory::create_termination_conditions(population_metadata* population_metadata)
{
	std::vector<termination_condition*> termination_conditions;
	return termination_conditions;
}
