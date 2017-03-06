#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

string ShaderLoader::ReadShader(const char * filename)
{
	string shaderCode;
	ifstream file(filename, ios::in);

	if (!file.good()) {
		cout << "Can't read file " << filename << endl;
		throw std::runtime_error("can't load shader source");
	}

	file.seekg(0, ios::end);
	shaderCode.resize(static_cast<unsigned int>(file.tellg()));
	file.seekg(0, ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string &source, const char* shaderName)
{
	int compileResult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	//check for errors
	if(compileResult == GL_FALSE) {
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, nullptr, &shaderLog[0]);
		cout << "ERROR compiling shader: " << shaderName << endl << &shaderLog[0] << endl;
		throw std::runtime_error("Can't compile shader");
	}

	return shader;
}

GLuint ShaderLoader::CreateProgram(const char * vertexShaderFilename, const char * fragmentShaderFilename)
{
	// read the shader files and save the code
	string vertexShaderCode = ReadShader(vertexShaderFilename);
	string fragmentShaderCode = ReadShader(fragmentShaderFilename);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, "vertex_shader");
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "fragment_shader");

	int linkResult = 0;

	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	//check for link errors
	if (linkResult == GL_FALSE) {

		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, nullptr, &programLog[0]);
		cout << "Shader Loader: LINK ERROR" << endl << &programLog[0] << endl;
		cout << "Vertex shader: " << vertexShaderFilename << ", Fragment shader: " << fragmentShaderFilename << endl;
		throw std::runtime_error("Can't link shader programs");
	}
	return program;
}

