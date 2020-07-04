#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#define LOG(x) std::cout << x << std::endl

class Shader {

public:
	Shader() : Shader("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl") {  }
	Shader(const std::string vertexFile, const std::string fragmentFile);
	~Shader();
	
	void bind() { glUseProgram(programID); }
	void unbind() { glUseProgram(0); }

	void setUniform(const std::string name, int value);
	void setUniform(const std::string name, glm::vec3 value);
	void setUniform(const std::string name, float x, float y, float z);
	void setUniform(const std::string name, glm::mat4 value);
	
private: 
	void compile(unsigned int shader);
	void printShaderLog(unsigned int shader);
	void printProgramLog();
	

private:
	unsigned int programID;
	
};