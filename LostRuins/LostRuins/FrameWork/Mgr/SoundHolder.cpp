#include "SoundHolder.h"
#include <assert.h>

SoundHolder* SoundHolder::instance = nullptr;

SoundHolder::SoundHolder()
{
	assert(instance == nullptr);
	instance = this;
}

SoundBuffer& SoundHolder::GetBuffer(string filename)
{
	auto& map = instance->mapBuffer;
	auto it = map.find(filename);
	if (it == map.end())
	{
		auto& buffer = map[filename];
		buffer.loadFromFile(filename);
	}

	return map[filename];
}
