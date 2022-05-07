#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"

class ZombieCrawler : public Monster
{
private:

public:
	ZombieCrawler();
	virtual void MonsterInit();
};
