#pragma once
#include <AzCore/std/containers/ring_buffer.h>
#include <MyGem/BallBus.h>
#include <MyGem/BallSpawnerBus.h>
#include <Source/AutoGen/BallSpawnerComponent.AutoComponent.h>

namespace MyGem
{
    class BallSpawnerComponentController
        : public BallSpawnerComponentControllerBase
        , public BallSpawnerRequestBus::Handler
        , public BallNotificationBus::Handler
    {
    public:
        BallSpawnerComponentController(BallSpawnerComponent& parent);

        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override;

        // BallRequestBus
        void RespawnBall() override;

        // BallNotificationBus
        void OnBallSpawned(AZ::Entity* e) override;

    private:
        AzFramework::EntitySpawnTicket m_ticket;
        AZStd::ring_buffer<AZ::Entity*> m_balls;

        void RemoveOldBall();
    };
}