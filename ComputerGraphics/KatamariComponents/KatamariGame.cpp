#pragma once﻿
#include "KatamariGame.h"
#include "../Components/GridComponent.h"
#include "KatamariTrash.h"
#include "../Components/RectangleComponent.h"
#include "KatamariBall.h"
#include "../Tools/DataProcesser.h"

using namespace DirectX;
using namespace SimpleMath;

KatamariGame::KatamariGame() : Game(L"Katamari Game", 800, 800), cameraController(this)
{
    srand(static_cast<unsigned>(time(nullptr)));

    ball = new KatamariBall(this);
    ball->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    components_.push_back(ball);

    RectangleComponent* quad = new RectangleComponent(this, L"Textures/road.dds");
    quad->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Left, XM_PI / 2.0f));
    quad->SetScale(Vector3::One * 1000.0f);
    components_.push_back(quad);


    input_dev_->MouseMove.AddRaw(&cameraController, &CameraController::OnMouseMove);

    // for (int i = 0; i < 10; ++i)
    // {
    //     KatamariTrash* gabriel = new KatamariTrash(this, "Models/Gabriel.obj", L"Textures/white.dds", 0.9f, Vector3(0.0f, 0.0f, 0.0f));
    //     gabriel->SetScale(Vector3(0.005f, 0.005f, 0.005f));
    //     gabriel->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f, static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
    //     gabriel->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PI / 2.0f));
    //     gabriel->collision.Radius = 0.1f;
    //     components_.push_back(gabriel);
    //     furniture.push_back(gabriel);
    // }

    for (int i = 0; i < 10; ++i)
    {
        KatamariTrash* melon = new KatamariTrash(this, "Models/earth.obj", L"Textures/earth.dds", 2.0f,
                                                 Vector3(0.0f, 0.0f, 0.0f));
        melon->SetScale(Vector3(10.f, 10.f, 10.f));
        melon->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f,
                                   static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        melon->shininess = 1000.f;
        melon->specularColor = DirectX::SimpleMath::Vector3(5.0f, 1.0f, 0.0f);
        melon->diffuseColor = DirectX::SimpleMath::Vector3(5.0f, 1.0f, 0.0f);
        melon->collision.Radius = 1.f;
        components_.push_back(melon);
        furniture.push_back(melon);
    }


    for (int i = 0; i < 10; ++i)
    {
        KatamariTrash* cucumber = new KatamariTrash(this, "Models/pumpkin.obj", L"Textures/white.dds", 0.9f,
                                                    Vector3(0.0f, 0.0f, 0.0f));
        cucumber->SetScale(Vector3(2.0f, 2.0f, 2.0f));
        cucumber->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f,
                                      static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        cucumber->collision.Radius = 0.8f;
        components_.push_back(cucumber);
        furniture.push_back(cucumber);
    }
    for (int i = 0; i < 10; ++i)
    {
        KatamariTrash* cucumber = new KatamariTrash(this, "Models/pumpkin.obj", L"Textures/yellow.dds", 0.9f,
                                                    Vector3(0.0f, 0.0f, 0.0f));
        cucumber->SetScale(Vector3(5.0f, 5.0f, 5.0f));
        cucumber->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f,
                                      static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        cucumber->collision.Radius = 0.8f;
        components_.push_back(cucumber);
        furniture.push_back(cucumber);
    }
    cameraController.targetBall = ball;
}

void KatamariGame::Update()
{
    cameraController.Update();
    Vector3 dir = Vector3::Zero;
    if (input_dev_->IsKeyDown(Keys::W))
    {
        dir += Camera->Target - Camera->Position;
    }
    if (input_dev_->IsKeyDown(Keys::S))
    {
        dir -= Camera->Target - Camera->Position;
    }
    if (input_dev_->IsKeyDown(Keys::A))
    {
        dir -= (Camera->Target - Camera->Position).Cross(Camera->Up);
    }
    if (input_dev_->IsKeyDown(Keys::D))
    {
        dir += (Camera->Target - Camera->Position).Cross(Camera->Up);
    }

    if (input_dev_->IsKeyDown(Keys::Space))
    {
        if (!SpacePressed)
        {
            ball->Jump();
            SpacePressed = true;
        }
    }
    else
    {
        SpacePressed = false;   
    }
    dir.y = ball->currentJump;

    std::cout << dir.y << "\n";
    if (dir.Length() > 0.0f)
        ball->SetDirection(dir);

    Game::Update();
}

void KatamariGame::PrepareFrame()
{
    context_->ClearState();

    context_->RSSetState(rast_state_);

    context_->OMSetRenderTargets(1, &render_view_, depth_stencil_view_);

    context_->VSSetShader(DataProcesser::GetVertexShader("spinny"), nullptr, 0);
    context_->PSSetShader(DataProcesser::GetPixelShader("spinny"), nullptr, 0);

    context_->PSSetSamplers(0, 1, &sampler_state_);

    SetBackgroundColor();
    context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
