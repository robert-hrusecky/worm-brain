/*
 * PreviewWindow.cpp
 *
 *  Created on: Aug 1, 2017
 *      Author: robert
 */

#include "PreviewWindow.h"

namespace EvolutionSimulator
{

PreviewWindow::PreviewWindow(const glm::vec2& position, int side) :
		m_frameBuffer(side, side), m_rect(position, side, side)
{
	int sideLength = Creature::NUM_SEGMENTS * Creature::SEGMENT_LENGTH * SCALE;
	m_camera.init(sideLength, sideLength);
	m_camera.setScale(10.0f);
	m_camera.update();
}

PreviewWindow::~PreviewWindow()
{
	remove();
}

void PreviewWindow::setCreature(Creature* creature)
{
	if (m_world != nullptr)
	{
		return;
	}
	m_creature = creature;
	b2Vec2 gravity(0.0f, -9.81f);
	m_world = new b2World(gravity);
	b2BodyDef groundDef;
	groundDef.position.Set(0.0f, -2.5f);
	groundDef.type = b2_staticBody;

	b2PolygonShape groundShape;
	groundShape.SetAsBox(100.0f, 2.0f);
	b2FixtureDef groundFixtrueDef;
	groundFixtrueDef.shape = &groundShape;
	groundFixtrueDef.density = 1.0;
	groundFixtrueDef.friction = 1.0f;
	b2Body* body = m_world->CreateBody(&groundDef);
	body->CreateFixture(&groundFixtrueDef);
	m_creature->add(m_world);
}

void PreviewWindow::remove()
{
	if (m_world == nullptr)
	{
		return;
	}
	m_creature->clearBody();
	delete m_world;
	m_world = nullptr;
}

void PreviewWindow::update(float deltaTime, SnowEngine::InputManager& inputManager,
		SnowEngine::Camera2D camera)
{
	if (m_world == nullptr)
	{
		return;
	}
	glm::vec2 coords = inputManager.getMouseCoords();
	camera.convertScreenToWorldCoords(coords);
	glm::vec2 offset = glm::abs(coords - glm::vec2(m_rect.x, m_rect.y));
	if (offset.x < m_rect.z / 2.0f && offset.y < m_rect.w / 2.0f)
	{
		m_creature->update();
		m_world->Step(deltaTime / 1000.0f, 8, 3);
		b2Vec2 cameraTarget = m_creature->getPosition();
		m_camera.setPosition(glm::vec2(cameraTarget.x, cameraTarget.y));
		m_camera.update();
	}
}

void PreviewWindow::draw(SnowEngine::DebugRenderer& renderer)
{
	if (m_world == nullptr)
	{
		return;
	}
	renderer.drawBox(glm::vec4(0.0f, -2.5f, 200.0f, 4.0f), 0.0f, SnowEngine::ColorRGBA8());
	for (unsigned int i = 0; i <= 10; i++)
	{
		renderer.drawBox(glm::vec4(i * 10.0f, 0.0f, 1.0f, 9.0f), 0.0f,
				SnowEngine::ColorRGBA8(255, 0, 0, 255));
	}
	m_creature->draw(renderer);
	renderer.end();
	m_frameBuffer.begin();
	renderer.render(m_camera.getCameraMatrix());
	m_frameBuffer.end();
}

void PreviewWindow::render(SnowEngine::SpriteBatch& spriteBatch)
{
	if (m_world == nullptr)
	{
		return;
	}
	m_frameBuffer.draw(spriteBatch, m_rect);
}

} /* namespace EvolutionSimulator */
