
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>

#include <assert.h>

#define LOG(x) std::cout << x << std::endl

bool checkOpenGLError(std::string msg) {

	bool foundError = false;
	int glErr = glGetError();

	while (glErr != GL_NO_ERROR) {
		LOG(msg << "glError: " << glErr);
		foundError = true;
		glErr = glGetError();
	}

	return foundError;
}


//implementation from TheCherno
std::string ReadFile(const std::string& filepath)
{
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
			in.close();
		}
		else
		{
			std::cout << "Could not read from file " << filepath << std::endl;
		}
	}
	else
	{
		std::cout << "Could not open file " << filepath << std::endl;
	}

	return result;
}


float RandomFloat(float min, float max)
{
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	float range = max - min;
	return (random*range) + min;
}