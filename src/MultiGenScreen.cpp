/*
 * MultiGenScreen.cpp
 *
 *  Created on: Aug 3, 2017
 *      Author: robert
 */

#include "MultiGenScreen.h"
#include <iostream>

namespace EvolutionSimulator
{

MultiGenScreen::MultiGenScreen(SnowEngine::IMainGame* game) :
		SnowEngine::IGameScreen(game)
{
	m_camera.init(m_game->getScreenWidth(), m_game->getScreenHeight());
	m_camera.update();
	m_renderer.init(m_game->getShaderCache());
}

MultiGenScreen::~MultiGenScreen()
{

}

void MultiGenScreen::onStart()
{
	unsigned int numThreads = std::thread::hardware_concurrency();
	m_joinRequested = false;
	for (unsigned int i = 0; i < numThreads; i++)
	{
		m_workerThreads.emplace_back([&]()
		{
			int i = 0;
			while (true)
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				if (m_joinRequested)
				{
					break;
				}
				if (m_queue.empty())
				{
					m_cond.wait(lock, [&]()
							{	return !m_queue.empty();});

				}
			}
		});
	}
}

void MultiGenScreen::onPause()
{
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_joinRequested = true;
	}
	for (auto& thread : m_workerThreads)
	{
		thread.join();
	}
	m_workerThreads.clear();
}

void MultiGenScreen::update(float deltaTime, SnowEngine::InputManager& inputManager)
{
	m_angle += deltaTime / 1000.0f;
	m_camera.update();
}

void MultiGenScreen::onEvent(const SDL_Event& evnt)
{
}

void MultiGenScreen::draw()
{
	m_renderer.drawBox(glm::vec4(0, 0, 100, 100), m_angle, SnowEngine::ColorRGBA8());
	m_renderer.end();
	m_renderer.render(m_camera.getCameraMatrix());
}

void MultiGenScreen::setPopulation(Population& population)
{
	m_population = &population;
}

} /* namespace EvolutionSimulator */
