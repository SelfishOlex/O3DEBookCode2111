#include <AzFramework/Components/TransformComponent.h>
#include <AzFramework/Physics/RigidBodyBus.h>
#include <Multiplayer/BallSpawnerComponent.h>
#include <Multiplayer/Components/NetworkTransformComponent.h>
#include <MyGem/BallSpawnerBus.h>

namespace MyGem
{
    BallSpawnerComponentController::BallSpawnerComponentController(
        BallSpawnerComponent& parent)
        : BallSpawnerComponentControllerBase(parent){}

    void BallSpawnerComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        const AZ::EntityId me = GetEntity()->GetId();
        BallSpawnerRequestBus::Handler::BusConnect(me);
        BallNotificationBus::Handler::BusConnect(me);
        m_balls.set_capacity(2);
        RespawnBall();
    }

    void BallSpawnerComponentController::OnDeactivate(
        Multiplayer::EntityIsMigrating)
    {
        BallSpawnerRequestBus::Handler::BusDisconnect();
        BallNotificationBus::Handler::BusDisconnect();
    }

    void BallSpawnerComponentController::RespawnBall()
    {
        RemoveOldBall();

        using namespace AzFramework;
        AZ::Transform world = GetParent().GetTransformComponent()->
            GetWorldTM();
        m_ticket = AzFramework::EntitySpawnTicket{ GetBallAsset() };

        auto cb = [world](
            EntitySpawnTicket::Id /*ticketId*/,
            SpawnableEntityContainerView view)
        {
            const AZ::Entity* e = *view.begin();
            if (auto* tc = e->FindComponent<TransformComponent>())
            {
                tc->SetWorldTM(world);
            }
        };

        SpawnAllEntitiesOptionalArgs optionalArgs;
        optionalArgs.m_preInsertionCallback = AZStd::move(cb);
        SpawnableEntitiesInterface::Get()->SpawnAllEntities(
            m_ticket, AZStd::move(optionalArgs));
    }

    void BallSpawnerComponentController::OnBallSpawned(AZ::Entity* e)
    {
        m_balls.push_back(e);
    }

    void BallSpawnerComponentController::RemoveOldBall()
    {
        if (m_balls.empty() == false)
        {
            AZ::Entity* previousBall = m_balls.back();

            using RigidBus = Physics::RigidBodyRequestBus;
            RigidBus::Event(previousBall->GetId(),
                &RigidBus::Events::DisablePhysics);

            using namespace Multiplayer;
            const ConstNetworkEntityHandle oldBall(previousBall);

            AZ::Interface<IMultiplayer>::Get()->
                GetNetworkEntityManager()->MarkForRemoval(oldBall);
        }
    }
}
