#pragma once
#include <AzCore/Component/Component.h>
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>

namespace MyProject
{
    // An example of spawning prefab from C++.
    class MySpawnerComponent : public AZ::Component
    {
    public:
        AZ_COMPONENT(MySpawnerComponent,
            "{F75160EB-CB82-4A41-8AB0-68AD43B9625B}");

        // AZ::Component overrides
        void Activate() override;
        void Deactivate() override {}

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* reflection);

    private:
        AZ::Data::Asset<AzFramework::Spawnable> m_spawnableAsset;
        AzFramework::EntitySpawnTicket m_ticket;
    };
}