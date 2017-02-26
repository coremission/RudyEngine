#include "Engine.hpp"
#include <GL/glew.h>

Engine::Engine() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
}

Engine::~Engine() {
    
}