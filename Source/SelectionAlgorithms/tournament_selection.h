#ifndef _TOURNAMENT_SELECTION_H_
#define _TOURNAMENT_SELECTION_H_

#include <memory>

#include "../API/galapagos.h"
#include "../API/selection_algorithm.h"
#include "../API/stochastic.h"

struct tournament_selection_metadata : selection_algorithm_metadata, galapagos_metadata<selection_algorithm_metadata, tournament_selection_metadata> {
    const size_t tournament_size;

    explicit tournament_selection_metadata(const size_t tournament_size) : tournament_size{tournament_size} {}
};

class tournament_selection : public selection_algorithm {
private:
    const tournament_selection_metadata& _metadata;
    stochastic& _stochastic_instance;

public:
  inline tournament_selection(const tournament_selection_metadata& metadata, stochastic& stochastic_instance) :
          _metadata{metadata}, _stochastic_instance{stochastic_instance} {}

  [[nodiscard]] std::shared_ptr<creature> invoke(const std::shared_ptr<const population>& population) const override;
};

#endif /* _TOURNAMENT_SELECTION_H_ */
