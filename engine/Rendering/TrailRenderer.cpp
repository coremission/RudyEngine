#include "TrailRenderer.h"
#include <iostream>

TrailRenderer::TrailRenderer(GameObject* _gameObject):
	Renderer(nullptr), // triangle strip mesh
	gameObject(_gameObject)
{
}

TrailRenderer::~TrailRenderer()
{
}

void TrailRenderer::render() const
{
	std::cout << "trail render" << std::endl;
}