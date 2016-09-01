#pragma once
//delta and total time

class Timer 
{
	float currentTime;
	float prevTime;
	float deltaTime;

public:
	bool init();
	bool step();
	bool term();

	//fixed to start of frame
	float getDeltaTime()const;
	//Fixed to start of frame
	float getTotalTime()const;

	// Return the real passage of time
	float getRealTime()const;
};