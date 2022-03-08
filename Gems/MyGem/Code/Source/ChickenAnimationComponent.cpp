#include <ChickenAnimationComponent.h>
#include <AzCore/Serialization/EditContext.h>
#include <Integration/AnimGraphComponentBus.h>

namespace MyGem
{
    void ChickenAnimationComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<ChickenAnimationComponent, AZ::Component>()
              ->Field("Actor", &ChickenAnimationComponent::m_actor)
              ->Version(1);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                ec->Class<ChickenAnimationComponent>(
                    "Chicken Animation",
                    "[Player controlled chicken]")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(
                        Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("Game"))
                    ->DataElement(nullptr,
                        &ChickenAnimationComponent::m_actor,
                        "Actor", "Entity with chicken actor.");
            }
        }
    }

    void ChickenAnimationComponent::Activate()
    {
        ChickenNotificationBus::Handler::BusConnect(GetEntityId());
    }

    void ChickenAnimationComponent::Deactivate()
    {
        ChickenNotificationBus::Handler::BusDisconnect();
    }

    void ChickenAnimationComponent::OnChickenSpeedChanged(float s)
    {
        using namespace EMotionFX::Integration;
        AnimGraphComponentRequestBus::Event(m_actor,
            &AnimGraphComponentRequests::SetNamedParameterFloat,
                "Speed", s);
    }
} // namespace MyGem
