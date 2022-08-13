#pragma once
#include <map>
#include "Transition.h"
#include <string>
#include <memory>

class TransitionManager
{
private:
	void loadTransitions();
public:
	TransitionManager();
	std::map<std::string, std::unique_ptr<Transition>> transitions;
	void play(std::string name);
};

