/*
 * MainScreen.cpp
 *
 *  Created on: Jul 30, 2017
 *      Author: robert
 */

#include "MainScreen.h"

#include <snow/VertexData.h>
#include <glm/glm.hpp>

#include "GenerationScreen.h"
#include "MultiGenScreen.h"
namespace EvolutionSimulator
{

MainScreen::MainScreen(SnowEngine::IMainGame* game) :
		SnowEngine::IGameScreen(game), m_population(0), m_bestPreview(glm::vec2(0, 150), 150), m_liveGenButton(
				SnowEngine::ColorRGBA8(0, 255, 0, 255), glm::vec4(-100, 0, 100, 100)), m_multiGenButton(
				SnowEngine::ColorRGBA8(), glm::vec4(100, 0, 100, 100))
{
	m_camera.init(m_game->getScreenWidth(), m_game->getScreenHeight());
	m_renderer.init(m_game->getShaderCache());
	m_spriteBatch.init(m_game->getShaderCache());
}

MainScreen::~MainScreen()
{

}

void MainScreen::onStart()
{
	if (m_generation > 0)
	{
		m_population.sort();
		m_bestPreview.setCreature(m_population.getCreatures()[0]);
	}
}

void MainScreen::onPause()
{
}

void MainScreen::update(float deltaTime, SnowEngine::InputManager& inputManager)
{
	m_bestPreview.update(deltaTime, inputManager, m_camera);
	m_camera.update();
	if (m_liveGenButton.isPressed(inputManager, m_camera))
	{
		m_bestPreview.remove();
		if (m_generation > 0)
		{
			m_population.evolve();
		}
		GenerationScreen* genScreen = (GenerationScreen*) m_game->getScreen("GenerationScreen");
		genScreen->setPopulation(m_population);
		m_game->setActiveScreen("GenerationScreen");
		m_generation++;
	}
	else if (m_multiGenButton.isPressed(inputManager, m_camera))
	{
		m_bestPreview.remove();
		if (m_generation > 0)
		{
			m_population.evolve();
		}
		MultiGenScreen* genScreen = (MultiGenScreen*) m_game->getScreen("MultiGenScreen");
		genScreen->setPopulation(m_population);
		m_game->setActiveScreen("MultiGenScreen");
		m_generation += MultiGenScreen::GENS;
	}
}

void MainScreen::onEvent(const SDL_Event& evnt)
{
}

void MainScreen::draw()
{
	m_liveGenButton.draw(m_renderer);
	m_multiGenButton.draw(m_renderer);
	m_renderer.end();
	m_renderer.render(m_camera.getCameraMatrix());

	m_bestPreview.draw(m_renderer);

	m_spriteBatch.begin();
	m_bestPreview.render(m_spriteBatch);
	m_spriteBatch.end();
	m_spriteBatch.renderBatch(m_camera.getCameraMatrix());
}

} /* namespace EvolutionSimulator */
