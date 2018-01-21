/*
 * GenerationScreen.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: robert
 */

#include "GenerationScreen.h"

#include <random>

namespace EvolutionSimulator
{

GenerationScreen::GenerationScreen(SnowEngine::IMainGame* game) :
		SnowEngine::IGameScreen(game)
{
	m_camera.init(m_game->getScreenWidth(), m_game->getScreenHeight());
	m_camera.setScale(10.0f);
	m_camera.update();
	m_renderer.init(m_game->getShaderCache());
}

GenerationScreen::~GenerationScreen()
{

}

void GenerationScreen::onStart()
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

	for (unsigned int i = 0; i < m_creatures.size(); i++)
	{
		m_worlds.push_back(new b2World(gravity));
		b2Body* body = m_worlds[i]->CreateBody(&groundDef);
		body->CreateFixture(&groundFixtrueDef);
		m_creatures[i]->add(m_worlds[i]);
	}

	m_frameCounter = 0;
}

void GenerationScreen::onPause()
{
	for (unsigned int i = 0; i < m_worlds.size(); i++)
	{
		m_creatures[i]->clearBody();
		delete m_worlds[i];
	}
	m_worlds.clear();
}

void GenerationScreen::update(float deltaTime, SnowEngine::InputManager& inputManager)
{
	if (m_frameCounter >= FRAMES)
	{
		for (unsigned int i = 0; i < m_creatures.size(); i++)
		{
			m_creatures[i]->assignFitness();
		}
		m_game->setActiveScreen("MainScreen");
	}
	else
	{
		for (unsigned int i = 0; i < m_creatures.size(); i++)
		{
			m_creatures[i]->update();
			m_worlds[i]->Step(deltaTime / 1000.0f, 8, 3);
		}
		b2Vec2 cameraTarget(0.0f, 0.0f);
		for (unsigned int i = 0; i < m_creatures.size(); i++)
		{
			cameraTarget += m_creatures[i]->getPosition();
		}
		cameraTarget *= 1.0f / m_creatures.size();

		m_camera.setPosition(glm::vec2(cameraTarget.x, cameraTarget.y));
		m_camera.update();
		m_frameCounter++;
	}
}

void GenerationScreen::onEvent(const SDL_Event& evnt)
{
}

void GenerationScreen::draw()
{
	m_renderer.drawBox(glm::vec4(0.0f, -2.5f, 200.0f, 4.0f), 0.0f, SnowEngine::ColorRGBA8());
	for (unsigned int i = 0; i <= 10; i++)
	{
		m_renderer.drawBox(glm::vec4(i * 10.0f, 0.0f, 1.0f, 9.0f), 0.0f,
				SnowEngine::ColorRGBA8(255, 0, 0, 255));
	}
	for (unsigned int i = 0; i < m_creatures.size(); i++)
	{
		m_creatures[i]->draw(m_renderer);
	}
	m_renderer.end();
	m_renderer.render(m_camera.getCameraMatrix());
}

void GenerationScreen::setPopulation(Population& population)
{
	m_creatures = population.getCreatures();
}

} /* namespace EvolutionSimulator */
