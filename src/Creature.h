/*
 * Creature.h
 *
 *  Created on: Jul 27, 2017
 *      Author: robert
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <Box2D/Box2D.h>
#include <random>
#include <vector>
#include <snow/DebugRenderer.h>
#include <snow/VertexData.h>

#include "NeuralNetwork.h"

namespace EvolutionSimulator
{

class Creature
{
public:
	static constexpr int NUM_SEGMENTS = 6;
	static constexpr float SEGMENT_LENGTH = 5.0f;
	static constexpr float SEGMENT_HEIGHT = 1.0f;
	static constexpr float TORQUE_MULTIPLIER = 1000.0f;

	Creature(std::mt19937_64& generator);
	Creature(Creature* other, std::mt19937_64& generator);
	virtual ~Creature();
	void add(b2World* world);
	void remove(b2World* world);
	void applyTorqureToJoint(float torque, int index);
	void update();
	void draw(SnowEngine::DebugRenderer& renderer);
	b2Vec2 getPosition();
	void assignFitness();
	float getFitness();
	void clearBody();
private:
	std::vector<b2Body*> m_segments;
	std::vector<b2RevoluteJoint*> m_joints;
	NeuralNetwork m_brain;
	float m_fitness = 0.0f;
	SnowEngine::ColorRGBA8 m_color;
};

} /* namespace EvolutionSimulator */

#endif /* CREATURE_H_ */
