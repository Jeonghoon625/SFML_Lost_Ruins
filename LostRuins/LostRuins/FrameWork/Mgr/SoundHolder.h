#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

using namespace sf;
using namespace std;

class SoundHolder
{
public:
	SoundHolder();

	static SoundBuffer& GetBuffer(string filename);
private:
	map<string, SoundBuffer> mapBuffer;

	static SoundHolder* instance;
};

