#pragma once

class Transition
{
public:
	bool transitionEnded = false;
	virtual void play();
	virtual void reset();
};

