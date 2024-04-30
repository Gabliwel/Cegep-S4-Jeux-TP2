#pragma once

struct Inputs
{
	Inputs()
	{
		reset();
	}

	void reset()
	{
		horizontal = 0;
		jump = false;
	}

	int horizontal;
	bool jump; 
	bool isInPause = false;
	bool isInPauseBuffer = false;
};