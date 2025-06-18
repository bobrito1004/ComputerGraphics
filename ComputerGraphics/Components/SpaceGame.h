#pragma once
#include "unordered_map"
#include "Game.h"
#include "CameraController.h"
#include "CelestialBody.h"



class SpaceGame : public Game
{
protected:
	void SetBackgroundColor() override;
public:
	std::unordered_map<std::string, CelestialBody*> celestialBodies;
	std::vector<std::string> toRemove = {};
	CameraController controller;
	SpaceGame();
	void Update() override;
	void ApplyGravity(CelestialBody* currentBody, const std::unordered_map<std::string, CelestialBody*>& allBodies);

};
