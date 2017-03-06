#include "ShaderProgram.h"
#include "ShaderLoader.h"
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& materialName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath):
	_materialName(materialName), _programId(ShaderLoader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()))
{
	// TODO: attempt to create universal class for material
	/*int count = 0;
	int bufSize = 0;
	int length = 100;
	int size = 100;
	GLuint type = 0;
	char name[100];
	GLuint uniformLocation = 0;

	glGetProgramiv(_programId, GL_ACTIVE_UNIFORMS, &count);
	printf("Active Uniforms: %d\n", count);

	for (int i = 0; i < count; i++)
	{
		glGetActiveUniform(_programId, uniformLocation, bufSize, &length, &size, &type, name);
		_uniformsMap.insert(std::make_pair(std::string(name), uniformLocation));
		
		printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
	}*/
}

ShaderProgram::~ShaderProgram()
{
	std::cout << "~material.destructor " << _materialName << std::endl;
	glDeleteProgram(_programId);
}

// cache
constexpr char * DEFAULT_SPRITE_MATERIAL = "simple_sprite_material";

// static field declaration
std::map<std::string, std::shared_ptr<ShaderProgram> > ShaderProgram::programsCache;

std::shared_ptr<ShaderProgram> ShaderProgram::get(const std::string& materialName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	bool alreadyExist = programsCache.find(materialName) != programsCache.end();
	if (alreadyExist)
		return programsCache[materialName];

	auto sharedMaterial = std::make_shared<ShaderProgram>(materialName, vertexShaderPath, fragmentShaderPath);
	programsCache[materialName] = sharedMaterial;
	return sharedMaterial;
}

std::shared_ptr<ShaderProgram> ShaderProgram::getDefaultSpriteProgram()
{
	return get(DEFAULT_SPRITE_MATERIAL, "Shaders\\Vertex.glsl", "Shaders\\Fragment.glsl");
}
