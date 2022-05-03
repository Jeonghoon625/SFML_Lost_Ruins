#include <iostream>
#include "FrameWork/FrameWork.h"

int main()
{
	FrameWork lostRuins;

	if (false == lostRuins.Initialize())
	{
		puts("Failed Initialize");

		return 1;
	}

	return lostRuins.Run();
}