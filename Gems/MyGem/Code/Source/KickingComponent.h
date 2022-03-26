#pragma once
#include <AzCore/Component/Component.h>
#include <AzFramework/Physics/Common/PhysicsEvents.h>

namespace MyGem
{
    class KickingComponent
        : public AZ::Component
    {
    public:
        AZ_COMPONENT(KickingComponent,
            "{73A60188-9BFB-4168-A733-8A06BC500ECB}");

        static void Reflect(AZ::ReflectContext* rc);

        KickingComponent();

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override {}

    private:
        AzPhysics::SceneEvents::
            OnSceneTriggersEvent::Handler m_trigger;
        void OnTriggerEvents(
            const AzPhysics::TriggerEventList& tel);

        float m_kickForce = 1000.f;

        void KickBall(AZ::EntityId ball);

        AZ::Vector3 GetBallPosition(AZ::EntityId ball);
        AZ::Vector3 GetSelfPosition();
        void AddImpulseToBall(AZ::Vector3 v, AZ::EntityId ball);
    };
} // namespace MyGem
