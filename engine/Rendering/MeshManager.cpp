#include "MeshManager.h"

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

constexpr char * const QUAD_MESH_ID = "rudy_quad";
constexpr char * const SPRITE_QUAD_MESH_ID = "rudy_sprite_quad";
constexpr char * const CUBEMAP_MESH_ID = "rudy_cubemap_mesh";
constexpr char * const INDEXED_QUAD_MESH_ID = "indexed_cube_mesh";
constexpr char * const SKYBOX_CUBE_MESH_ID = "indexed_skybox_mesh";

std::map<std::string, std::shared_ptr<LegacyMesh>> MeshManager::meshMap;

shared_ptr<LegacyMesh> MeshManager::registerMesh(std::string id, vector<VertexData> vertices)
{
	auto mesh = make_shared<LegacyMesh>(vertices);
	meshMap[id] = mesh;
	return mesh;
}

std::shared_ptr<LegacyMesh> MeshManager::registerMesh(std::string id, std::vector<VertexData> vertices, std::vector<GLuint> indices)
{
	auto mesh = make_shared<LegacyMesh>(vertices, indices);
	meshMap[id] = mesh;
	return mesh;
}

shared_ptr<LegacyMesh> MeshManager::getQuadMesh()
{
	bool quadMeshCreated = meshMap.find(QUAD_MESH_ID) != meshMap.end();
	if (quadMeshCreated)
		return meshMap[QUAD_MESH_ID];

	auto lb = VertexData{ vec3(-1.0f, -1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f) };
	auto lt = VertexData{ vec3(-1.0f,  1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) };
	auto br = VertexData{ vec3( 1.0f, -1.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f) };
	auto tr = VertexData{ vec3( 1.0f,  1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f) };

	vector<VertexData> vertices;
	vertices.push_back(lb);
	vertices.push_back(lt);
	vertices.push_back(br);

	vertices.push_back(lt);
	vertices.push_back(tr);
	vertices.push_back(br);

	return registerMesh(QUAD_MESH_ID, vertices);
}

std::shared_ptr<LegacyMesh> MeshManager::getIndexedQuadMesh()
{
	bool meshCreated = meshMap.find(INDEXED_QUAD_MESH_ID) != meshMap.end();
	if (meshCreated)
		return meshMap[INDEXED_QUAD_MESH_ID];

	auto v0 = VertexData{ vec3( 1.0f, -1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) };
	auto v1 = VertexData{ vec3(-1.0f, -1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	auto v2 = VertexData{ vec3(-1.0f,  1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	auto v3 = VertexData{ vec3( 1.0f, -1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	auto v4 = VertexData{ vec3( 1.0f,  1.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	auto v5 = VertexData{ vec3(-1.0f, -1.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) };

	vector<VertexData> vertices {v0, v1, v2, v3, v4, v5};
	
	vector<GLuint> indices{ 0, 1, 2,
							3, 4, 5,
						  };
	
	return registerMesh(INDEXED_QUAD_MESH_ID, vertices, indices);
}

std::shared_ptr<BaseMesh> MeshManager::getSkyboxMesh()
{
	bool skyBoxMeshCreated = meshMap.find(CUBEMAP_MESH_ID) != meshMap.end();
	if (skyBoxMeshCreated)
		return meshMap[CUBEMAP_MESH_ID];

	GLuint meshVbo;
	GLuint meshVao;

	GLfloat cubemapVertices[] = {
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &meshVao);
	glBindVertexArray(meshVao);

	glGenBuffers(1, &meshVbo);
	glBindBuffer(GL_ARRAY_BUFFER, meshVbo);

	int bufferSize = sizeof(cubemapVertices);

	glBufferData(GL_ARRAY_BUFFER, bufferSize, &cubemapVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);
	glEnableVertexAttribArray(0);

	return std::make_shared<BaseMesh>(meshVao);
}

std::shared_ptr<BaseMesh> MeshManager::getDefaultSpriteMesh()
{
	bool spriteMeshCreated = meshMap.find(SPRITE_QUAD_MESH_ID) != meshMap.end();
	if (spriteMeshCreated)
		return meshMap[SPRITE_QUAD_MESH_ID];

	auto lb = VertexData{ vec3(-1.0f, -1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f) };
	auto lt = VertexData{ vec3(-1.0f,  1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f) };
	auto br = VertexData{ vec3(1.0f, -1.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f) };
	auto tr = VertexData{ vec3(1.0f,  1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f) };

	vector<VertexData> vertices;
	vertices.push_back(lb);
	vertices.push_back(lt);
	vertices.push_back(br);

	vertices.push_back(lt);
	vertices.push_back(tr);
	vertices.push_back(br);

	return registerMesh(SPRITE_QUAD_MESH_ID, vertices);
}