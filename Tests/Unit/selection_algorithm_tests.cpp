#include "../../Source/API/galapagos.h"
#include "../../Source/API/creature.h"
#include "../../Source/SelectionAlgorithms/tournament_selection.h"

#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../catch.hpp"
#include "../fakeit.hpp"

using namespace catch
using namespace fakeit;

TEST_CASE( "tournament selection invoked", "[selection algorithm][tournament selection]" ) {
  size_t tournament_size = 2;
  int desired_creature_index = 1;

  Mock<stochastic> stochastic_mock;
  When(OverloadedMethod(stochastic_mock, rand_int, int(int))).Return(0,0,1);
  stochastic* mocked_stochastic = &stochastic_mock.get();

  Mock<creature> creature_mock0;
  When(Method(creature_mock0, get_fitness)).AlwaysReturn(1);
  creature* mocked_creature0 = &creature_mock0.get();

  Mock<creature> creature_mock1;
  When(Method(creature_mock1, get_fitness)).AlwaysReturn(2);
  creature* mocked_creature1 = &creature_mock1.get();

  Mock<population> population_mock;
  When(Method(population_mock, get_size)).AlwaysReturn(2);
  When(Method(population_mock, get_creature)).AlwaysDo([mocked_creature0, mocked_creature1](int i) {
    return i == 0 ? mocked_creature0 : mocked_creature1;
  });
  population* mocked_population = &population_mock.get();

  galapagos_session& session = galapagos_session::get_instance();
  session.__stochastic__ = mocked_stochastic;

  tournament_selection selection_algorithm = tournament_selection(tournament_size);
  creature* selected_creature = selection_algorithm.invoke(mocked_population);
  creature* desired_creature = mocked_population->get_creature(desired_creature_index);

  REQUIRE(selected_creature == desired_creature)

  delete mocked_stochastic;
  delete mocked_creature0;
  delete mocked_creature1;
  delete mocked_population;

  return error_code;
}
