#include "Mutex.h"

std::mutex & Mutex::Get()
{
	static std::mutex mtx;
	return mtx;
}
