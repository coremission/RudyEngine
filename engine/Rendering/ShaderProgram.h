#ifndef MATERIAL_H
#define MATERIAL_H

#include <glew/glew.h>
#include <string>
#include <memory>
#include <map>

class ShaderProgram
{
private:
	GLuint _programId; 
	std::string _materialName;
public:
	~ShaderProgram();
	GLuint programId() const { return _programId; }
	ShaderProgram(const std::string &materialName, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
// Shader programs cache
private:
	static std::map<std::string, std::shared_ptr<ShaderProgram>> programsCache;
public:
	static std::shared_ptr<ShaderProgram> get(const std::string& programName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	static std::shared_ptr<ShaderProgram> getDefaultSpriteProgram();

};
#endif // MATERIAL_H