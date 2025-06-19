#pragma once

#include "../Components/Game.h"
#include "../Components/CameraController.h"

class KatamariTrash;
class KatamariBall;

class KatamariGame : public Game
{
protected:
    CameraController cameraController;
public:
    KatamariBall* ball;
    bool SpacePressed = false;
    std::vector<KatamariTrash*> furniture{};
    KatamariGame();
    void Update() override;
    void PrepareFrame() override;
};