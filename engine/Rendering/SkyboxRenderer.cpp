#include "SkyboxRenderer.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include <iostream>

SkyboxRenderer::SkyboxRenderer(Camera * const _camera, std::vector<std::string> filenames):
	Renderer(MeshManager::getSkyboxMesh()),
	cubeMapTextureId(createCubemap(filenames)),
	camera(_camera)
{
	std::cout << "skybox renderer created" << std::endl;
}

void SkyboxRenderer::render() const
{
	// 0. reset depth mask
	glDepthMask(GL_FALSE);
	// 0.5. wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// 1. bind skybox vao
	glBindVertexArray(mesh->vao);

	// 2. use skybox program
	glUseProgram(shaderProgram->programId());

	// 3. bind uniforms
	//// 3.1 cubemap
	glActiveTexture(cubeMapTextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureId);

	//// 3.2 view projection matrix
	GLuint vpLocation = glGetUniformLocation(shaderProgram->programId(), "OrientationMatrix");
	glm::mat4 orientationMatrix = camera->getOrientationMatrix();
	glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &orientationMatrix[0][0]);

	// 4. draw skybox
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// 5. set depth mask back
	glDepthMask(GL_TRUE);

	// 6. set wirframe back
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

SkyboxRenderer::~SkyboxRenderer()
{
}

GLuint SkyboxRenderer::createCubemap(std::vector<std::string> filenames)
{
	GLuint id;

	// 1. generate skybox texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	// 2. load 6 images
	/*
	GL_TEXTURE_CUBE_MAP_POSITIVE_X
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	*/

	for (GLuint i = 0; i < 6; i++) {
		std::vector<unsigned char> image;
		unsigned long width, height;

		TextureManager::loadPng(filenames[i], image, width, height);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
			width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	}

	// 3. set cubemap texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return id;
}
