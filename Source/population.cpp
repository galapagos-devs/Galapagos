#ifndef _POPULATION_CPP_
#define _POPULATION_CPP_

#include "../Headers/API/population.h"

#include <vector>
#include <algorithm>

#include "../Headers/API/creature.h"
#include "../Headers/API/Factory/genetic_factory.h"
#include "../Headers/API/galapagos_metadata.h"

class population_internal : population {
	/*
	The internal implementation of the population object from the public API.
	*/
private:
	population_metadata* _population_metadata;

	std::vector<creature*> _creatures;
	creature* _optimal_creature;
	
public:
	population_internal(population_metadata* population_metadata)
	{
		_population_metadata = population_metadata;

		_creatures.resize(get_size());
		_optimal_creature = nullptr;
	}

	~population_internal() {
		for (size_t i = 0; i < get_size(); i++)
			delete _creatures[i];
	}

	// Returns the number of creaters in the population.
	size_t get_size() override {
		return _population_metadata->size;
	}

	creature* operator[] (int i) override {
		return _creatures[i];
	}

	// Returns the most optimal creature in turms of fitness.
	creature* get_optimal_creature() override {
		return _optimal_creature;
	}

	// Progresses the genetic algorithum until the termination conditions are met.
	void evolve() override {
		selection_algorithm* selection_algorithm = genetic_factory::create_selection_algorithm(_population_metadata);
		std::vector<termination_condition*> termination_conditions = genetic_factory::create_termination_conditions(_population_metadata);

		std::vector<creature*> new_generation;
		new_generation.resize(get_size());

		while (_has_terminated(termination_conditions)) {
			size_t surviving_creature_count = _elitism(new_generation);
			_breed_new_generation(new_generation, surviving_creature_count, selection_algorithm);
		}

		// clean-up memory
		delete selection_algorithm;
		for (size_t i = 0; i < termination_conditions.size(); i++)
			delete termination_conditions[i];
	}

private:
	creature* _find_optimal_creature() {
		creature* optimal_creature = nullptr;
		double optimal_fitness = 0;

		size_t size = get_size();
		for (size_t i = 0; i < size; i++) {
			creature* current_creature = _creatures[i];
			double current_fitness = current_creature->get_fitness();

			if (current_fitness > optimal_fitness) {
				optimal_fitness = current_fitness;
				optimal_creature = current_creature;
			}
		}

		return optimal_creature;
	}

	// Copies the n best creatures into the next generation based on the survival rate as definied in the metadata.
	size_t _elitism(std::vector<creature*>& new_generation) {
		size_t population_size = get_size();

		// Sorts the creatures by decending fitness
		std::sort(_creatures.begin(), _creatures.end(), [](creature* x, creature* y) {
			return x->get_fitness() > y->get_fitness();
			});  //TODO - check the complexity of this sort

		size_t surviving_creature_count = (size_t)(_population_metadata->survival_rate * population_size);
		for (size_t i = 0; i < surviving_creature_count; i++)
			new_generation[i] = _creatures[i];

		return surviving_creature_count;
	}

	// Breeds population_size - surviving_creature_count, new creates from the current population.
	void _breed_new_generation(std::vector<creature*>& new_generation, size_t surviving_creature_count, selection_algorithm* selection_algorithm) {
		size_t population_size = get_size();

		for (size_t i = surviving_creature_count; i < population_size; i++) {
			creature* parent1 = selection_algorithm->invoke(this);
			creature* parent2 = selection_algorithm->invoke(this);
			creature* child = parent1->breed_with(parent2);
			new_generation[i] = child;
		}

		for (size_t i = 0; i < population_size; i++) {
			delete _creatures[i];
			_creatures[i] = new_generation[i];
		}
	}

	// Checks if any of the termination conditions have been met.
	bool _has_terminated(std::vector<termination_condition*>& termination_conditions) {
		size_t num_termination_conditions = termination_conditions.size();

		for (size_t i = 0; i < num_termination_conditions; i++) {
			termination_condition* current_termination_condition = termination_conditions[i];
			if (current_termination_condition->invoke(this))
				return true;
		}
		return false;
	}
};

#endif /* _POPULATION_CPP_ */