#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(instance == nullptr);
	instance = this;
}

Texture& TextureHolder::GetTexture(std::string filename)
{
	// 1. filename key map에 있냐 없냐?
	// 2-1. 있다 맵에서 찾아서 반환
	// 2-2. 없다 만들어서 map insert
	
	auto& map = instance->mapTexture;

	auto it = map.find(filename);

	if (it == map.end())
	{
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}

	return map[filename];
}
