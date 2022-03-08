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

        AZ::EntityId m_ball;
        float m_kickForce = 1000.f;

        void KickBall();

        AZ::Vector3 GetBallPosition() const;
        AZ::Vector3 GetSelfPosition() const;
        void AddImpulseToBall(const AZ::Vector3& v);
    };
} // namespace MyGem
