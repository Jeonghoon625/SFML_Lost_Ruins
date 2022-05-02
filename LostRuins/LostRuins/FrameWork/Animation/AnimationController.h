#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationClip.h"
#include <map>
#include <queue>

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips;
	std::queue<std::string> playQueue;

	AnimationClip* currentClip;

	bool isPlaying;
	int currentFrame;
	int totalFrame;
	float frameDurtion;

	float accumTime;
	float speed;

	Sprite* sprite;

public:
	AnimationController();

	void SetTarget(Sprite* sprite);
	void AddClip(const AnimationClip& newClip);

	void Update(float dt);

	void Play(std::string clipId, bool clear = true);
	void PlayQueue(std::string clipId);

	void Stop();

	bool IsPlaying();

	float GetSpeed();
	void SetSpeed(float speed);

	void ClearPlayQueue();
};

