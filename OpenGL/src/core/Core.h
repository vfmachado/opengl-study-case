#pragma once

#include <iostream>

#define LOG(x) std::cout << x << std::endl

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)