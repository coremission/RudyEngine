#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <glad/glad.h>
#include <string>

class ShaderLoader
{
private:
	static std::string ReadShader(const char *filename);
	static GLuint CreateShader(GLenum shaderType, std::string& source, const char *shaderName);
public:
	static GLuint CreateProgram(const char * vertexShaderFilename, const char * fragmentShaderFilename);
};
#endif // SHADERLOADER_H
