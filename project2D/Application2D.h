#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "PhysicsScene.h"


class Application2D : public aie::Application {
public:
	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	aie::Renderer2D* GetRenderer();

	PhysicsScene* physScene;
protected:

	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;
	aie::Renderer2D*	m_2dRenderer;

	float m_cameraX, m_cameraY;
	float m_timer;
};

Application2D* GetApp();