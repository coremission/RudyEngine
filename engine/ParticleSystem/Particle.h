#ifndef PARTICLE_h
#define PARTICLE_h

#include <glm/glm.hpp>

struct Particle
{
	glm::vec3 position;

	Particle() = default;
	~Particle();
};

#endif //PARTICLE_h