/*
 * Population.h
 *
 *  Created on: Jul 29, 2017
 *      Author: robert
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include <vector>
#include <random>

#include "Creature.h"
namespace EvolutionSimulator
{

class Population
{
public:
	const static unsigned int SIZE = 100;
	Population(unsigned int seed);
	virtual ~Population();
	void sort();
	void evolve();
	std::vector<Creature*>& getCreatures();
private:
	std::mt19937_64 m_generator;
	std::vector<Creature*> m_creatures;
};

} /* namespace EvolutionSimulator */

#endif /* POPULATION_H_ */
