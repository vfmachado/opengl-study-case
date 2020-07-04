#include "Shader.h"

#include "../Utils.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string vertexFile, const std::string fragmentFile)
{
	std::string vertexSource = ReadFile(vertexFile);
	std::string fragmentSource = ReadFile(fragmentFile);

	LOG("VERTEX:\n" << vertexSource);
	LOG("FRAGMENT:\n" << fragmentSource);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//attach shader sources.
	const char *cVertexSource = vertexSource.c_str();
	const char *cfragmentSource = fragmentSource.c_str();

	glShaderSource(vertexShader, 1, &cVertexSource, NULL);
	glShaderSource(fragmentShader, 1, &cfragmentSource, NULL);

	//VERTEX
	compile(vertexShader);

	//FRAGMENT
	compile(fragmentShader);


	programID = glCreateProgram();
	
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);

	glLinkProgram(programID);

	checkOpenGLError();

	int programLinked;
	glGetProgramiv(programID, GL_LINK_STATUS, &programLinked);
	if (programLinked != 1) {
		printProgramLog();
	}

	LOG("Shader created. ID: " << programID);
	
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}


void Shader::setUniform(const std::string name, int value)
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform1i(location, value);
}

void Shader::setUniform(const std::string name, float x, float y, float z)
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniform3f(location, x, y, z);
}

void Shader::setUniform(const std::string name, glm::vec3 value)
{
	this->setUniform(name, value.x, value.y, value.z);
}

void Shader::setUniform(const std::string name, glm::mat4 value)
{
	int location = glGetUniformLocation(programID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::compile(unsigned int shader) {

	glCompileShader(shader);

	checkOpenGLError();

	int compiledStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledStatus);
	if (compiledStatus != 1) {
		printShaderLog(shader);
	}

}


void Shader::printShaderLog(unsigned int shader) 
{
	int length;
	int chWrittn = 0;
	char *log;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log = new char[length];
		glGetShaderInfoLog(shader, length, &chWrittn, log);

		LOG("Shader Info LOG: " << log);
		delete log;

	}
}

void Shader::printProgramLog() 
{
	int length = 0;
	int chWrittn = 0;
	char *log;

	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		log = new char[length];
		glGetProgramInfoLog(programID, length, &chWrittn, log);
		LOG("Program Info LOG: " << log);
		delete log;
	}
}
