/*
 * MainScreen.h
 *
 *  Created on: Jul 30, 2017
 *      Author: robert
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_

#include <snow/Camera2D.h>
#include <snow/DebugRenderer.h>
#include <snow/IGameScreen.h>
#include <snow/IMainGame.h>
#include <snow/InputManager.h>
#include <snow/ShaderProgram.h>
#include <SDL2/SDL.h>

#include "Button.h"
#include "Population.h"
#include "PreviewWindow.h"
namespace EvolutionSimulator
{

class MainScreen : public SnowEngine::IGameScreen
{
public:
	MainScreen(SnowEngine::IMainGame* game);
	virtual ~MainScreen();
	void onStart();
	void onPause();
	void update(float deltaTime, SnowEngine::InputManager& inputManager);
	void onEvent(const SDL_Event& evnt);
	void draw();
private:
	SnowEngine::Camera2D m_camera;
	SnowEngine::DebugRenderer m_renderer;
	SnowEngine::SpriteBatch m_spriteBatch;
	Population m_population;
	PreviewWindow m_bestPreview;
	Button m_liveGenButton, m_multiGenButton;
	unsigned int m_generation = 0;
};

} /* namespace EvolutionSimulator */

#endif /* MAINSCREEN_H_ */
