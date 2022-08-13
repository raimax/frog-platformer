#include "TransitionManager.h"
#include "FadeIn.h"
#include "FadeOut.h"

TransitionManager::TransitionManager()
{
	loadTransitions();
}

void TransitionManager::play(std::string name)
{
	transitions[name].get()->play();
}

void TransitionManager::loadTransitions()
{
	transitions.insert(std::make_pair("fade_in", std::make_unique<FadeIn>()));
	transitions.insert(std::make_pair("fade_out", std::make_unique<FadeOut>()));
}
