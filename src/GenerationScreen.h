/*
 * GamePlayScreen.h
 *
 *  Created on: Jun 24, 2017
 *      Author: robert
 */

#ifndef GENERATIONSCREEN_H_
#define GENERATIONSCREEN_H_

#include <snow/Camera2D.h>
#include <snow/DebugRenderer.h>
#include <snow/IGameScreen.h>
#include <snow/IMainGame.h>
#include <Box2D/Box2D.h>
#include <vector>
#include "Creature.h"
#include "Population.h"

namespace EvolutionSimulator
{

class GenerationScreen : public SnowEngine::IGameScreen
{
public:
	static const unsigned int FRAMES = 900;
	GenerationScreen(SnowEngine::IMainGame* game);
	virtual ~GenerationScreen();

	void onStart();
	void onPause();
	void update(float deltaTime, SnowEngine::InputManager& inputManager);
	void onEvent(const SDL_Event& evnt);
	void draw();
	void setPopulation(Population& population);
private:
	SnowEngine::Camera2D m_camera;
	SnowEngine::DebugRenderer m_renderer;
	std::vector<Creature*> m_creatures;
	std::vector<b2World*> m_worlds;
	unsigned int m_frameCounter = 0;
};

} /* namespace EvolutionSimulator */

#endif /* GAMEPLAYSCREEN_H_ */
