/*
 * MultiGenScreen.h
 *
 *  Created on: Aug 3, 2017
 *      Author: robert
 */

#ifndef MULTIGENSCREEN_H_
#define MULTIGENSCREEN_H_

#include <snow/Camera2D.h>
#include <snow/DebugRenderer.h>
#include <snow/IGameScreen.h>
#include <snow/IMainGame.h>
#include <snow/InputManager.h>
#include <vector>

#include "Creature.h"
#include "Population.h"
#include "ThreadPool.h"

namespace EvolutionSimulator
{

class MultiGenScreen : public SnowEngine::IGameScreen
{
public:
	MultiGenScreen(SnowEngine::IMainGame* game);
	virtual ~MultiGenScreen();
	void onStart();
	void onPause();
	void update(float deltaTime, SnowEngine::InputManager& inputManager);
	void onEvent(const SDL_Event& evnt);
	void draw();
	void setPopulation(Population& population);
private:
	SnowEngine::Camera2D m_camera;
	SnowEngine::DebugRenderer m_renderer;
	float m_angle = 0.0f;
	bool m_finished = false;

	ThreadPool<unsigned int*> m_threads;
	std::vector<unsigned int*> m_data;

	Population* m_population = nullptr;
};

} /* namespace EvolutionSimulator */

#endif /* MULTIGENSCREEN_H_ */
