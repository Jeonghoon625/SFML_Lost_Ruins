#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class TextureHolder
{
public:
	TextureHolder();
	static Texture& GetTexture(std::string filename);

private:
	std::map<std::string, Texture> mapTexture;

	static TextureHolder* instance;
};