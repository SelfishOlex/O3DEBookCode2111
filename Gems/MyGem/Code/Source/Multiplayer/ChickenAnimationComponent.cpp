#include <AzCore/Serialization/SerializeContext.h>
#include <Integration/AnimGraphComponentBus.h>
#include <Multiplayer/ChickenAnimationComponent.h>
#include <Source/AutoGen/ChickenMovementComponent.AutoComponent.h>

namespace MyGem
{
    void ChickenAnimationComponent::Reflect(AZ::ReflectContext* rc)
    {
        auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
        if (sc)
        {
            sc->Class<ChickenAnimationComponent,
                ChickenAnimationComponentBase>()->Version(1);
        }
        ChickenAnimationComponentBase::Reflect(rc);
    }

    ChickenAnimationComponent::ChickenAnimationComponent()
        : m_velocityChangedEvent([this](AZ::Vector3 velocity)
            {
                OnVelocityChanged(velocity);
            })
    {}

    void ChickenAnimationComponent::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        GetChickenMovementComponent()->VelocityAddEvent(
            m_velocityChangedEvent);
    }

    void ChickenAnimationComponent::OnVelocityChanged(
        AZ::Vector3 velocity)
    {
        velocity.SetZ(0);

        using namespace EMotionFX::Integration;
        AnimGraphComponentRequestBus::Event(GetEntityId(),
            &AnimGraphComponentRequests::SetNamedParameterFloat,
            "Speed", velocity.GetLength());
    }
}
