/*
 * MultiGenScreen.cpp
 *
 *  Created on: Aug 3, 2017
 *      Author: robert
 */

#include "MultiGenScreen.h"
#include "ThreadPool.h"
#include "GenerationScreen.h"
#include <Box2D/Box2D.h>
#include <iostream>

namespace EvolutionSimulator
{

MultiGenScreen::MultiGenScreen(SnowEngine::IMainGame* game)
	: SnowEngine::IGameScreen(game), m_threads(&MultiGenScreen::doGeneration)
{
	m_camera.init(m_game->getScreenWidth(), m_game->getScreenHeight());
	m_camera.update();
	m_renderer.init(m_game->getShaderCache());
}

MultiGenScreen::~MultiGenScreen() {}

void MultiGenScreen::onStart()
{
	m_threads.start();
	m_gensLeft = GENS;
	m_threads.enqueue(m_population->getCreatures());
}

void MultiGenScreen::onPause() { m_threads.stop(true); }

void MultiGenScreen::update(float deltaTime, SnowEngine::InputManager& inputManager)
{
	m_angle += deltaTime / 1000.0f;
	m_camera.update();
	if (m_threads.isDone())
	{
		m_gensLeft--;
		if (m_gensLeft > 0)
		{
			m_population->sort();
			m_population->evolve();
			m_threads.enqueue(m_population->getCreatures());
		}
		else
		{
			m_game->setActiveScreen("MainScreen");
		}
	}
}

void MultiGenScreen::onEvent(const SDL_Event& evnt) {}

void MultiGenScreen::draw()
{
	m_renderer.drawBox(glm::vec4(0, 0, 100, 100), m_angle, SnowEngine::ColorRGBA8());
	m_renderer.end();
	m_renderer.render(m_camera.getCameraMatrix());
}

void MultiGenScreen::setPopulation(Population& population) { m_population = &population; }

void MultiGenScreen::doGeneration(Creature* creature)
{
	b2BodyDef groundDef;
	groundDef.position.Set(0.0f, -2.5f);
	groundDef.type = b2_staticBody;

	b2PolygonShape groundShape;
	groundShape.SetAsBox(100.0f, 2.0f);
	b2FixtureDef groundFixtrueDef;
	groundFixtrueDef.shape = &groundShape;
	groundFixtrueDef.density = 1.0;
	groundFixtrueDef.friction = 1.0f;

	b2Vec2 gravity(0.0f, -9.81f);

	b2World* world = new b2World(gravity);
	b2Body* body = world->CreateBody(&groundDef);
	body->CreateFixture(&groundFixtrueDef);
	creature->add(world);

	for (unsigned int i = 0; i < GenerationScreen::FRAMES; i++)
	{
		creature->update();
		world->Step(GenerationScreen::DELTA_TIME, 8, 3);
	}
	creature->assignFitness();
	creature->clearBody();

	delete world;
}

} /* namespace EvolutionSimulator */
