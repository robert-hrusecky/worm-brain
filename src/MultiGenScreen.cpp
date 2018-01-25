/*
 * MultiGenScreen.cpp
 *
 *  Created on: Aug 3, 2017
 *      Author: robert
 */

#include "MultiGenScreen.h"
#include "ThreadPool.h"
#include <iostream>

void func(unsigned int* ptr);

namespace EvolutionSimulator
{

MultiGenScreen::MultiGenScreen(SnowEngine::IMainGame* game) : SnowEngine::IGameScreen(game), m_threads(&func)
{
	m_camera.init(m_game->getScreenWidth(), m_game->getScreenHeight());
	m_camera.update();
	m_renderer.init(m_game->getShaderCache());
}

MultiGenScreen::~MultiGenScreen() {}

void MultiGenScreen::onStart()
{
	m_threads.start();

	for (unsigned int i = 0; i < 20; i++)
	{
		unsigned int* val = new unsigned int;
		*val = 40;
		m_data.push_back(val);
	}

	m_threads.enqueue(m_data);
}

void MultiGenScreen::onPause()
{
	m_threads.stop(true);
	for (auto val : m_data)
	{
		delete val;
	}
}

void MultiGenScreen::update(float deltaTime, SnowEngine::InputManager& inputManager)
{
	m_angle += deltaTime / 1000.0f;
	m_camera.update();
	if (!m_finished && m_threads.isDone())
	{
		m_finished = true;
		for (auto val : m_data)
		{
			std::cout << *val << std::endl;
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

} /* namespace EvolutionSimulator */

unsigned int fib(unsigned int n)
{
	if (n < 2)
	{
		return n;
	}

	return fib(n - 1) + fib(n - 2);
}

void func(unsigned int* ptr) {
	*ptr = fib(*ptr);
}
