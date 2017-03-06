#ifndef PARTICLE_SYSTEM_h
#define PARTICLE_SYSTEM_h

#include "Particle.h"
#include <Model/Component.h>
#include <Rendering/ShaderProgram.h>

#include <vector>
#include <memory>

class ParticleSystem: public Component
{
private:
	GLuint vao;
	GLuint instaceBuffer;
	const int MaxParticlesCount;
	std::vector<Particle> particles;
	std::shared_ptr<ShaderProgram> material;

	void createBaseQuad();
	void updateParticles();
public:
	explicit ParticleSystem(GameObject* game_object);
	void Start() override;
	void Update() override;
	~ParticleSystem() override;
};

#endif //PARTICLE_SYSTEM_h