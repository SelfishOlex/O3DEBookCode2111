#include <ChickenControllerComponent.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/CharacterBus.h>

namespace MyGem
{
    using namespace StartingPointInput;

    void ChickenControllerComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<ChickenControllerComponent, AZ::Component>()
                ->Field("Speed", &ChickenControllerComponent::m_speed)
                ->Version(1);

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<ChickenControllerComponent>("Chicken Controller",
                    "[Player controlled chicken]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("Game"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(nullptr, &ChickenControllerComponent::m_speed, 
                        "Speed", "Chicken's speed");
            }
        }
    }

    void ChickenControllerComponent::Activate()
    {
        InputEventNotificationBus::MultiHandler::BusConnect(MoveFwdEventId);
        AZ::TickBus::Handler::BusConnect();
    }

    void ChickenControllerComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
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
            m_forward = value;
        }
    }

    void ChickenControllerComponent::OnReleased([[maybe_unused]] float value)
    {
        const InputEventNotificationId* inputId = InputEventNotificationBus::GetCurrentBusId();
        if (inputId == nullptr)
        {
            return;
        }

        if (*inputId == MoveFwdEventId)
        {
            m_forward = 0.f;
        }
    }

    void ChickenControllerComponent::OnTick(float, AZ::ScriptTimePoint)
    {
        const ChickenInput input = CreateInput();
        ProcessInput(input);
    }

    ChickenInput ChickenControllerComponent::CreateInput()
    {
        ChickenInput input;
        input.m_forwardAxis = m_forward;

        return input;
    }

    void ChickenControllerComponent::UpdateVelocity(const ChickenInput& input)
    {
        const float currentHeading = GetEntity()->GetTransform()->GetWorldRotationQuaternion().GetEulerRadians().GetZ();
        const AZ::Vector3 fwd = AZ::Vector3::CreateAxisY(input.m_forwardAxis);
        m_velocity = AZ::Quaternion::CreateRotationZ(currentHeading).TransformVector(fwd) * m_speed;
    }

    void ChickenControllerComponent::ProcessInput(const ChickenInput& input)
    {
        UpdateVelocity(input);

        Physics::CharacterRequestBus::Event(GetEntityId(), 
            &Physics::CharacterRequestBus::Events::AddVelocity, m_velocity);
    }
} // namespace MyGem
