#pragma once
#include <Source/AutoGen/ChickenAnimationComponent.AutoComponent.h>

namespace MyGem
{
    class ChickenAnimationComponent
        : public ChickenAnimationComponentBase
    {
    public:
        AZ_MULTIPLAYER_COMPONENT(MyGem::ChickenAnimationComponent,
            s_chickenAnimationComponentConcreteUuid,
            MyGem::ChickenAnimationComponentBase);

        static void Reflect(AZ::ReflectContext* rc);
        ChickenAnimationComponent();

        void OnInit() override {}
        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override{}

    private:
        AZ::Event<AZ::Vector3>::Handler m_velocityChangedEvent;
        void OnVelocityChanged(AZ::Vector3 velocity);
    };
}