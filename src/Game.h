/*
 * Game.h
 *
 *  Created on: Jun 24, 2017
 *      Author: robert
 */

#ifndef GAME_H_
#define GAME_H_

#include <snow/IMainGame.h>

#include "Population.h"
namespace EvolutionSimulator
{

class Game : public SnowEngine::IMainGame
{
public:
	Game();
	virtual ~Game();
	void onStart();
	void onStop();
};

} /* namespace EvolutionSimulator */

#endif /* GAME_H_ */
