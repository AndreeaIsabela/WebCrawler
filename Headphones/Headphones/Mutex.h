#pragma once
#include <mutex>

class Mutex
{
public:
	static std::mutex & Get();
};
