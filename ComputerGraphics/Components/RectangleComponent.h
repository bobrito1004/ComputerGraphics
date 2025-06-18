#pragma once
#include "BaseComponent.h"
class RectangleComponent :
    public BaseComponent
{
public:
    explicit RectangleComponent(Game* g, const wchar_t* diffuseTextureName);
    void SetPosition(DirectX::SimpleMath::Vector3 p) override { position = p; }
    void SetRotation(DirectX::SimpleMath::Quaternion q) override { rotation = q; }
    void SetScale(DirectX::SimpleMath::Vector3 s) override { scale = s; }
};

