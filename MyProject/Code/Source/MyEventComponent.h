#pragma once
#include <AzCore/Component/Component.h>
#include <AzCore/Component/TransformBus.h>

namespace MyProject
{
    // An example of listening to movement events
    // of TransformComponent using an AZ::Event
    class MyEventComponent : public AZ::Component
    {
    public:
        AZ_COMPONENT(MyEventComponent,
            "{934BF061-204B-4695-944A-23A1BA7433CB}");

        static void GetRequiredServices(
            AZ::ComponentDescriptor::DependencyArrayType& required)
        {
            required.push_back(AZ_CRC_CE("TransformService"));
        }

        MyEventComponent();

        // AZ::Component overrides
        void Activate() override;
        void Deactivate() override {}

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* rc);

    private:
        AZ::TransformChangedEvent::Handler m_movementHandler;
        void OnWorldTransformChanged(const AZ::Transform& world);
    };
}