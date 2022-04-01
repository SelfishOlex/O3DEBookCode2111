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

    void ChickenSpawnComponent::OnChickenCreated(
        AZ::Entity* e, int team)
    {
        if (team >= 0 && team <= 1)
        {
            m_teams[team].push_back(e);
        }
    }

    NetworkEntityHandle ChickenSpawnComponent::OnPlayerJoin(
        [[maybe_unused]] uint64_t userId,
        const Multiplayer::MultiplayerAgentDatum&)
    {
        return { GetNextChicken() };
    }

    AZ::Entity* ChickenSpawnComponent::GetNextChicken()
    {
        AZStd::vector<AZ::Entity*>& team =
            m_teams[0].size() > m_teams[1].size() ?
            m_teams[0] : m_teams[1];
        if (team.empty()) return nullptr;

        AZ::Entity* newChicken = team.back();
        team.pop_back();

        return newChicken;
    }
} // namespace MyGem
