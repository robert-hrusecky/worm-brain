/*
 * Button.h
 *
 *  Created on: Jul 30, 2017
 *      Author: robert
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include <snow/Camera2D.h>
#include <snow/DebugRenderer.h>
#include <snow/InputManager.h>
#include <snow/VertexData.h>
#include <glm/glm.hpp>
namespace EvolutionSimulator
{

class Button
{
public:
	Button(const SnowEngine::ColorRGBA8& color, const glm::vec4& rect);
	virtual ~Button();
	bool isPressed(SnowEngine::InputManager& inputManager, SnowEngine::Camera2D& camera);
	void draw(SnowEngine::DebugRenderer& renderer);
private:
	SnowEngine::ColorRGBA8 m_color;
	glm::vec4 m_rect;
};

} /* namespace EvolutionSimulator */

#endif /* BUTTON_H_ */
