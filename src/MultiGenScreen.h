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
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Creature.h"
#include "Population.h"
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

	std::vector<std::thread> m_workerThreads;
	std::mutex m_mutex;
	std::condition_variable m_cond;
	unsigned int m_waitingThreads = 0;
	bool m_joinRequested = false;

//	std::vector<Creature*> m_queue;
	Population* m_population = nullptr;
	std::vector<int> m_queue;
};

} /* namespace EvolutionSimulator */

#endif /* MULTIGENSCREEN_H_ */
