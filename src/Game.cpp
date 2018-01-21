/*
 * Game.cpp
 *
 *  Created on: Jun 24, 2017
 *      Author: robert
 */

#include "Game.h"

#include "GenerationScreen.h"
#include "MainScreen.h"
#include "MultiGenScreen.h"

namespace EvolutionSimulator
{

Game::Game() :
		SnowEngine::IMainGame("WormBrain", 800, 600)
{

}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}

void Game::onStart()
{
	addScreen(new MainScreen(this), "MainScreen");
	addScreen(new GenerationScreen(this), "GenerationScreen");
	addScreen(new MultiGenScreen(this), "MultiGenScreen");
	setActiveScreen("MainScreen");
}

void Game::onStop()
{
}

} /* namespace EvolutionSimulator */
