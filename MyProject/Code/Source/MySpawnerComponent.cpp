#include "MySpawnerComponent.h"
#include <AzCore/Asset/AssetSerializer.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Components/TransformComponent.h>

using namespace MyProject;

void MySpawnerComponent::Activate()
{
    using namespace AzFramework;
    AZ::Transform world = GetEntity()->GetTransform()->GetWorldTM();
    m_ticket = EntitySpawnTicket(m_spawnableAsset);

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

    if (m_ticket.IsValid())
    {
        SpawnAllEntitiesOptionalArgs optionalArgs;
        optionalArgs.m_preInsertionCallback = AZStd::move(cb);
        SpawnableEntitiesInterface::Get()->SpawnAllEntities(
            m_ticket, AZStd::move(optionalArgs));
    }
}

void MySpawnerComponent::Reflect(AZ::ReflectContext* reflection)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(reflection);
    if (!sc) return;

    sc->Class<MySpawnerComponent, Component>()
        ->Field("Prefab", &MySpawnerComponent::m_spawnableAsset)
        ->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;

    using namespace AZ::Edit::Attributes;
    ec->Class<MySpawnerComponent>("My Spawner Component", 
        "[An example of spawning prefab from C++]")
      ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
        ->Attribute(Category, "My Project")
        ->DataElement(nullptr, &MySpawnerComponent::m_spawnableAsset, 
            "Prefab", 
            "Spawn this prefab once when this entity activates")
    ;
}
