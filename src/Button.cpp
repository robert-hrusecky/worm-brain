/*
 * Button.cpp
 *
 *  Created on: Jul 30, 2017
 *      Author: robert
 */

#include "Button.h"
#include <SDL2/SDL.h>

namespace EvolutionSimulator
{

Button::Button(const SnowEngine::ColorRGBA8& color, const glm::vec4& rect) :
		m_color(color), m_rect(rect)
{
}

Button::~Button()
{
	// TODO Auto-generated destructor stub
}

bool Button::isPressed(SnowEngine::InputManager& inputManager, SnowEngine::Camera2D& camera)
{
	if (!inputManager.isKeyDown(SDL_BUTTON_LEFT))
	{
		return false;
	}
	glm::vec2 coords = inputManager.getMouseCoords();
	camera.convertScreenToWorldCoords(coords);
	glm::vec2 offset = glm::abs(coords - glm::vec2(m_rect.x, m_rect.y));
	return offset.x < m_rect.z / 2.0f && offset.y < m_rect.w / 2.0f;

}

void Button::draw(SnowEngine::DebugRenderer& renderer)
{
	renderer.drawBox(m_rect, 0.0f, m_color);
}

} /* namespace EvolutionSimulator */
