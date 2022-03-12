#pragma once
#include <AzCore/Component/Component.h>
#include <Multiplayer/IMultiplayerSpawner.h>
#include <MyGem/ChickenBus.h>

namespace MyGem
{
    class ChickenSpawnComponent
        : public AZ::Component
        , public Multiplayer::IMultiplayerSpawner
        , public ChickenNotificationBus::Handler
    {
    public:
        AZ_COMPONENT(ChickenSpawnComponent,
            "{814BAF21-10E4-4BE9-8380-C23B0EC27205}");

        static void Reflect(AZ::ReflectContext* rc);

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // ChickenNotificationBus
        void OnChickenCreated(AZ::Entity* e) override;

        // IMultiplayerSpawner overrides
        Multiplayer::NetworkEntityHandle OnPlayerJoin(
            uint64_t userId,
            const Multiplayer::MultiplayerAgentDatum&) override;
        void OnPlayerLeave(
            Multiplayer::ConstNetworkEntityHandle entityHandle,
            const Multiplayer::ReplicationSet& replicationSet,
            AzNetworking::DisconnectReason reason) override {}

    private:
        AZ::Entity* m_chicken = nullptr;
    };
} // namespace MyGem
