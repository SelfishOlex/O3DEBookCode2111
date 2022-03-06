#include <ChickenControllerComponent.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/CharacterBus.h>

namespace MyGem
{
    using namespace StartingPointInput;

    void ChickenControllerComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<ChickenControllerComponent, AZ::Component>()
              ->Field("Speed", &ChickenControllerComponent::m_speed)
              ->Field("Turn Speed",
                    &ChickenControllerComponent::m_turnSpeed)
              ->Field("Gravity", &ChickenControllerComponent::m_gravity)
              ->Version(3);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                ec->Class<ChickenControllerComponent>(
                    "Chicken Controller",
                    "[Player controlled chicken]")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(
                        Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("Game"))
                    ->DataElement(nullptr,
                        &ChickenControllerComponent::m_turnSpeed,
                        "Turn Speed", "Chicken's turning speed")
                    ->DataElement(nullptr,
                        &ChickenControllerComponent::m_gravity,
                        "Gravity", "Gravity towards -Z")
                    ->DataElement(nullptr,
                        &ChickenControllerComponent::m_speed,
                        "Speed", "Chicken's speed");
            }
        }
    }

    void ChickenControllerComponent::Activate()
    {
        InputEventNotificationBus::MultiHandler::BusConnect(
            MoveFwdEventId);
        InputEventNotificationBus::MultiHandler::BusConnect(
            MoveRightEventId);
        InputEventNotificationBus::MultiHandler::BusConnect(
            RotateYawEventId);
        AZ::TickBus::Handler::BusConnect();
    }

    void ChickenControllerComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        InputEventNotificationBus::MultiHandler::BusDisconnect();
    }

    void ChickenControllerComponent::OnPressed(float value)
    {
        const InputEventNotificationId* inputId =
            InputEventNotificationBus::GetCurrentBusId();
        if (inputId == nullptr)
        {
            return;
        }

        if (*inputId == MoveFwdEventId)
        {
            m_forward = value;
        }
        else if (*inputId == MoveRightEventId)
        {
            m_strafe = value;
        }
        else if (*inputId == RotateYawEventId)
        {
            m_yaw = value;
        }
    }

    void ChickenControllerComponent::OnReleased(float value)
    {
        const InputEventNotificationId* inputId =
            InputEventNotificationBus::GetCurrentBusId();
        if (inputId == nullptr)
        {
            return;
        }

        if (*inputId == MoveFwdEventId)
        {
            m_forward = value;
        }
        else if (*inputId == MoveRightEventId)
        {
            m_strafe = value;
        }
        else if (*inputId == RotateYawEventId)
        {
            m_yaw = value;
        }
    }

    void ChickenControllerComponent::OnHeld(float value)
    {
        const InputEventNotificationId* inputId =
            InputEventNotificationBus::GetCurrentBusId();
        if (inputId == nullptr)
        {
            return;
        }

        if (*inputId == RotateYawEventId)
        {
            m_yaw = value;
        }
    }

    void ChickenControllerComponent::OnTick(float,
                                            AZ::ScriptTimePoint)
    {
        const ChickenInput input = CreateInput();
        ProcessInput(input);
    }

    ChickenInput ChickenControllerComponent::CreateInput()
    {
        ChickenInput input;
        input.m_forwardAxis = m_forward;
        input.m_strafeAxis = m_strafe;
        input.m_viewYaw = m_yaw;

        return input;
    }

    void ChickenControllerComponent::UpdateRotation(
        const ChickenInput& input)
    {
        AZ::TransformInterface* t = GetEntity()->GetTransform();

        float currentHeading = t->GetWorldRotationQuaternion().
            GetEulerRadians().GetZ();
        currentHeading += input.m_viewYaw * m_turnSpeed;
        AZ::Quaternion q =
            AZ::Quaternion::CreateRotationZ(currentHeading);

        t->SetWorldRotationQuaternion(q);
    }

    void ChickenControllerComponent::UpdateVelocity(
        const ChickenInput& input)
    {
        const float currentHeading = GetEntity()->GetTransform()->
            GetWorldRotationQuaternion().GetEulerRadians().GetZ();
        const AZ::Vector3 fwd = AZ::Vector3::CreateAxisY(
            input.m_forwardAxis);
        const AZ::Vector3 strafe = AZ::Vector3::CreateAxisX(
            input.m_strafeAxis);
        const AZ::Vector3 combined = (fwd + strafe).GetNormalized();
        m_velocity = AZ::Quaternion::CreateRotationZ(currentHeading).
            TransformVector(combined) * m_speed;
    }

    void ChickenControllerComponent::ProcessInput(
        const ChickenInput& input)
    {
        UpdateRotation(input);
        UpdateVelocity(input);

        Physics::CharacterRequestBus::Event(GetEntityId(),
            &Physics::CharacterRequestBus::Events::AddVelocity,
                m_velocity);
        Physics::CharacterRequestBus::Event(GetEntityId(),
            &Physics::CharacterRequestBus::Events::AddVelocity,
                AZ::Vector3::CreateAxisZ(m_gravity));
    }
} // namespace MyGem
