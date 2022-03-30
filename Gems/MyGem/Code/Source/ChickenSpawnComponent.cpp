#include <ChickenSpawnComponent.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/EditContext.h>
#include <Multiplayer/IMultiplayer.h>

namespace MyGem
{
    using namespace Multiplayer;

    void ChickenSpawnComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<ChickenSpawnComponent, AZ::Component>()
                ->Version(1);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                ec->Class<ChickenSpawnComponent>(
                    "Chicken Spawn",
                    "[Player controlled chickens]")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(
                        Attributes::AppearsInAddComponentMenu,
                        AZ_CRC_CE("Game"));
            }
        }
    }

    void ChickenSpawnComponent::Activate()
    {
        AZ::Interface<IMultiplayerSpawner>::Register(this);
        ChickenNotificationBus::Handler::BusConnect(GetEntityId());
    }

    void ChickenSpawnComponent::Deactivate()
    {
        ChickenNotificationBus::Handler::BusDisconnect();
        AZ::Interface<IMultiplayerSpawner>::Unregister(this);
    }

    void ChickenSpawnComponent::OnChickenCreated(AZ::Entity* e)
    {
        m_chicken = e;
    }

    NetworkEntityHandle ChickenSpawnComponent::OnPlayerJoin(
        [[maybe_unused]] uint64_t userId,
        const Multiplayer::MultiplayerAgentDatum&)
    {
        return NetworkEntityHandle{ m_chicken };
    }
} // namespace MyGem
