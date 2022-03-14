#pragma once
#include <AzCore/Component/TickBus.h>
#include <Source/AutoGen/ChickenCameraComponent.AutoComponent.h>

namespace MyGem
{
    class ChickenCameraComponentController
        : public ChickenCameraComponentControllerBase
        , public AZ::TickBus::Handler
    {
    public:
        ChickenCameraComponentController(ChickenCameraComponent& p);

        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override;

        // TickBus
        void OnTick(float deltaTime, AZ::ScriptTimePoint) override;
        int GetTickOrder() override;

    private:
        AZ::Entity* m_activeCameraEntity = nullptr;
        AZ::Entity* GetActiveCamera();
    };
}