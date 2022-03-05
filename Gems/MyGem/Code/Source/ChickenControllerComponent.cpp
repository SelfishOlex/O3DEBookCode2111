#include <ChickenControllerComponent.h>
#include <AzCore/Serialization/EditContext.h>

namespace MyGem
{
    using namespace StartingPointInput;

    void ChickenControllerComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<ChickenControllerComponent, AZ::Component>()
                ->Version(1);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                ec->Class<ChickenControllerComponent>("Chicken Controller",
                    "[Player controlled chicken]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("Game"));
            }
        }
    }

    void ChickenControllerComponent::Activate()
    {
        InputEventNotificationBus::MultiHandler::BusConnect(MoveFwdEventId);
    }

    void ChickenControllerComponent::Deactivate()
    {
        InputEventNotificationBus::MultiHandler::BusDisconnect();
    }

    void ChickenControllerComponent::OnPressed(float value)
    {
        const InputEventNotificationId* inputId = InputEventNotificationBus::GetCurrentBusId();
        if (inputId == nullptr)
        {
            return;
        }

        if (*inputId == MoveFwdEventId)
        {
            AZ_Printf("Chicken", "forward axis %f", value);
        }
    }

    void ChickenControllerComponent::OnReleased(float value)
    {
        const InputEventNotificationId* inputId = InputEventNotificationBus::GetCurrentBusId();
        if (inputId == nullptr)
        {
            return;
        }

        if (*inputId == MoveFwdEventId)
        {
            AZ_Printf("Chicken", "forward axis %f", value);
        }
    }
} // namespace MyGem
