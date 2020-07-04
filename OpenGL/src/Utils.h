#pragma once

#include <string>

bool checkOpenGLError(const std::string msg = "");

std::string ReadFile(const std::string& filepath);

float RandomFloat(float min, float max);