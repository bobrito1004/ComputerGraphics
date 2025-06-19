#include "CelestialBody.h"

#include "Game.h"

using namespace DirectX;
using namespace SimpleMath;

constexpr int SliceCount = 32;
constexpr int StackCount = 32;

CelestialBody::CelestialBody(Game* game, const CelestialBodyDesc& desc) :
    SphereComponent(game, desc.Radius, SliceCount, StackCount, desc.PrimaryColor, desc.SecondaryColor),
    spinAxis(desc.SpinAxis), spinSpeed(desc.SpinSpeed), orbitAnchor(desc.OrbitAnchor), orbitRadius(desc.OrbitRadius),
    orbitOrientationForward(desc.OrbitOrientationForward), orbitOrientationUp(desc.OrbitOrientationUp),
    orbitSpeed(desc.OrbitSpeed), absoluteVelocity(Vector3::Zero)
{
    if (orbitAnchor)
    {
        relativePosition = desc.OrbitOrientationForward * orbitRadius;
        position = orbitAnchor->position + relativePosition;

        orbit = new OrbitComponent(game, orbitRadius, 64, orbitAnchor->relativePosition,
                                   Vector4(0.5f, 0.5f, 0.5f, 1.0f)
        );
        orbit->Initialize();
    }
    else
    {
        position = desc.OrbitOrientationForward * orbitRadius;
    }
}

void CelestialBody::Update()
{
    SphereComponent::Update();
    if (orbitAnchor)
    {
        relativePosition = XMVector4Transform(relativePosition,
                                              Matrix::CreateFromAxisAngle(
                                                  orbitOrientationUp, game->delta_time_ * orbitSpeed));
        position = orbitAnchor->position + relativePosition;
        orbit->SetCenter(orbitAnchor->position);
    }
    else
    {
        position = XMVector4Transform(
            position, Matrix::CreateFromAxisAngle(orbitOrientationUp, game->delta_time_ * orbitSpeed));
    }
    rotation *= Quaternion::CreateFromAxisAngle(spinAxis, spinSpeed * game->delta_time_);

    position += absoluteVelocity * game->delta_time_;
}

void CelestialBody::Draw()
{
    SphereComponent::Draw();
 
}
