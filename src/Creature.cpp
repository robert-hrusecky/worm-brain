/*
 * Creature.cpp
 *
 *  Created on: Jul 27, 2017
 *      Author: robert
 */

#include "Creature.h"

namespace EvolutionSimulator
{

Creature::Creature(std::mt19937_64& generator) :
		m_brain(2 * (NUM_SEGMENTS - 1), NUM_SEGMENTS - 1, 1, 2 * NUM_SEGMENTS, generator)
{
	std::uniform_int_distribution<int> dist(0, 256);
	m_color.r = dist(generator);
	m_color.g = dist(generator);
	m_color.b = dist(generator);
}

Creature::Creature(Creature* other, std::mt19937_64& generator) :
		m_brain(other->m_brain, generator)
{
	std::uniform_int_distribution<int> dist(0, 256);
	m_color.r = dist(generator);
	m_color.g = dist(generator);
	m_color.b = dist(generator);
}

Creature::~Creature()
{
}

void Creature::add(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(-SEGMENT_LENGTH * NUM_SEGMENTS / 2.0f, 0.0f);
	bodyDef.type = b2_dynamicBody;

	b2PolygonShape shape;
	shape.SetAsBox(SEGMENT_LENGTH / 2.0f, SEGMENT_HEIGHT / 2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;

	m_segments.resize(NUM_SEGMENTS);
	for (unsigned int i = 0; i < m_segments.size(); i++)
	{
		bodyDef.position.x += SEGMENT_LENGTH * 3.0f / 4.0f;
		b2Body* segment = world->CreateBody(&bodyDef);
		segment->CreateFixture(&fixtureDef);
		m_segments[i] = segment;
	}

	b2RevoluteJointDef jointDef;
	for (unsigned int i = 0; i < m_segments.size() - 1; i++)
	{
		jointDef.Initialize(m_segments[i], m_segments[i + 1],
				b2Vec2(m_segments[i]->GetPosition().x + SEGMENT_LENGTH * 3.0f / 8.0f, 0.0f));
		b2RevoluteJoint* joint = (b2RevoluteJoint*) world->CreateJoint(&jointDef);
		m_joints.push_back(joint);
	}
}

void Creature::remove(b2World* world)
{
	for (unsigned int i = 0; i < m_joints.size(); i++)
	{
		world->DestroyJoint(m_joints[i]);
	}

	for (unsigned int i = 0; i < m_segments.size() - 1; i++)
	{
		world->DestroyBody(m_segments[i]);
	}
	clearBody();
}

void Creature::applyTorqureToJoint(float torque, int index)
{
	m_segments[index]->ApplyTorque(torque, true);
	m_segments[index + 1]->ApplyTorque(-torque, true);
}

void Creature::update()
{
	std::vector<double> inputs;
	for (unsigned int i = 0; i < m_joints.size(); i++)
	{
		inputs.push_back(m_joints[i]->GetJointAngle());
		inputs.push_back(m_joints[i]->GetJointSpeed());
	}
	const std::vector<double>& outputs = m_brain.getOutputs(inputs);
	for (unsigned int i = 0; i < outputs.size(); i++)
	{
		applyTorqureToJoint((outputs[i] * 2.0 - 1.0) * TORQUE_MULTIPLIER, i);
	}
}

void Creature::draw(SnowEngine::DebugRenderer& renderer)
{
	for (unsigned int i = 0; i < m_segments.size(); i++)
	{
		b2Body* segment = m_segments[i];
		renderer.drawBox(
				glm::vec4(segment->GetPosition().x, segment->GetPosition().y, SEGMENT_LENGTH,
						SEGMENT_HEIGHT), segment->GetAngle(), m_color);
	}
}

void Creature::assignFitness()
{
	m_fitness = getPosition().x;
}

float Creature::getFitness()
{
	return m_fitness;
}

b2Vec2 Creature::getPosition()
{
	b2Vec2 pos(0.0f, 0.0f);
	for (unsigned int i = 0; i < m_segments.size(); i++)
	{
		pos += m_segments[i]->GetPosition();
	}
	pos *= 1.0f / m_segments.size();
	return pos;
}

void Creature::clearBody()
{
	m_segments.clear();
	m_joints.clear();
}

} /* namespace EvolutionSimulator */

