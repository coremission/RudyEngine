#include "ParticleSystem.h"
#include <Rendering/ShaderProgram.h>

#include <glm/glm.hpp>
#include <glew/glew.h>


ParticleSystem::ParticleSystem(GameObject* game_object) :
	Component(game_object),
	vao(0),
	instaceBuffer(0),
	MaxParticlesCount(4)
{
}

void ParticleSystem::createBaseQuad()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// common data
	GLuint billboard_vertex_buffer;
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);

	// instance data
	glGenBuffers(1, &instaceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instaceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), &particles[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	
	material = ShaderProgram::get("ParticlesBillboard", "Shaders\\ParticleBillboard_Vertex.glsl", "Shaders\\ParticleBillboard_Fragment.glsl");
}

void ParticleSystem::updateParticles()
{
	for (size_t i = 0; i < particles.size(); ++i) {
		particles[i].position += glm::vec3(i * 0.0001f, 0.0f, 0.0f);
	}
	glBindBuffer(GL_ARRAY_BUFFER, instaceBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particles.size(), &particles[0], GL_STATIC_DRAW);
}

void ParticleSystem::Start()
{
	// create particles
	for(int i = 0; i < MaxParticlesCount; ++i)
	{
		particles.push_back(Particle{glm::vec3(i * 0.02f, i * 0.02f, 1.0f)});
	}
	createBaseQuad();
}

void ParticleSystem::Update()
{
	// render in update temporary
	glUseProgram(material->programId());
	glBindVertexArray(vao);

	// update particles
	updateParticles();

	// draw
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, MaxParticlesCount);
	glBindVertexArray(0);
	glUseProgram(0);
}

ParticleSystem::~ParticleSystem()
{
}
