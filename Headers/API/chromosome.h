#ifndef _CHROMOSOME_H_
#define _CHROMOSOME_H_

class chromosome {
public:
	// TODO: can we use templates to avoid manual casts?
	virtual double get_distance(chromosome* other) abstract;
};

#endif /* _CHROMOSOME_H_ */