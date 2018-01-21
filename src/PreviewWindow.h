/*
 * PreviewWindow.h
 *
 *  Created on: Aug 1, 2017
 *      Author: robert
 */

#ifndef PREVIEWWINDOW_H_
#define PREVIEWWINDOW_H_

#include <Box2D/Box2D.h>
#include <snow/Camera2D.h>
#include <snow/DebugRenderer.h>
#include <snow/FrameBuffer.h>
#include <glm/glm.hpp>
#include <snow/InputManager.h>
#include <snow/ShaderProgram.h>
#include <snow/SpriteBatch.h>

#include "Creature.h"
namespace EvolutionSimulator
{

class PreviewWindow
{
public:
	static constexpr float SCALE = 10.0f;

	PreviewWindow(const glm::vec2& position, int side);
	virtual ~PreviewWindow();
	void setCreature(Creature* creature);
	void remove();
	void update(float deltaTime, SnowEngine::InputManager& inputManager, SnowEngine::Camera2D camera);
	void draw(SnowEngine::DebugRenderer& renderer);
	void render(SnowEngine::SpriteBatch& spriteBatch);
private:
	Creature* m_creature = nullptr;
	b2World* m_world = nullptr;
	SnowEngine::Camera2D m_camera;
	SnowEngine::FrameBuffer m_frameBuffer;
	glm::vec4 m_rect;
};

} /* namespace EvolutionSimulator */

#endif /* PREVIEWWINDOW_H_ */
