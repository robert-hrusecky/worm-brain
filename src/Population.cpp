/*
 * Population.cpp
 *
 *  Created on: Jul 29, 2017
 *      Author: robert
 */

#include "Population.h"

#include <algorithm>

namespace EvolutionSimulator
{

Population::Population(unsigned int seed) :
		m_generator(seed)
{
	while (m_creatures.size() < SIZE)
	{
		m_creatures.push_back(new Creature(m_generator));
	}
}

Population::~Population()
{
	for (unsigned int i = 0; i < m_creatures.size(); i++)
	{
		delete m_creatures[i];
	}
}

void Population::sort()
{
	std::stable_sort(m_creatures.begin(), m_creatures.end(), [](Creature* a, Creature* b)
	{
		return a->getFitness() > b->getFitness();
	});
}

void Population::evolve()
{
	for (unsigned int i = 0; i < SIZE / 2; i++)
	{
		delete m_creatures[i + SIZE / 2];
		m_creatures[i + SIZE / 2] = new Creature(m_creatures[i], m_generator);
	}
}

std::vector<Creature*>& Population::getCreatures()
{
	return m_creatures;
}

} /* namespace EvolutionSimulator */
