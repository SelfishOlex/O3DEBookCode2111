#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <Multiplayer/ChickenMovementComponent.h>
#include <Multiplayer/Components/NetworkCharacterComponent.h>
#include <Multiplayer/Components/NetworkTransformComponent.h>

namespace MyGem
{
    using namespace StartingPointInput;

    ChickenMovementComponentController::
      ChickenMovementComponentController(ChickenMovementComponent& p)
        : ChickenMovementComponentControllerBase(p) {}

    void ChickenMovementComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        InputEventNotificationBus::MultiHandler::BusConnect(
            MoveFwdEventId);
        InputEventNotificationBus::MultiHandler::BusConnect(
            MoveRightEventId);
        InputEventNotificationBus::MultiHandler::BusConnect(
            RotateYawEventId);
    }

    void ChickenMovementComponentController::OnDeactivate(
        Multiplayer::EntityIsMigrating)
    {
        InputEventNotificationBus::MultiHandler::BusDisconnect();
    }

    void ChickenMovementComponentController::CreateInput(
        Multiplayer::NetworkInput& input,
        [[maybe_unused]] float deltaTime)
    {
        // Inputs for your own component always exist
        auto chickenInput = input.FindComponentInput<
            ChickenMovementComponentNetworkInput>();

        chickenInput->m_forwardAxis = m_forward;
        chickenInput->m_strafeAxis = m_strafe;
        chickenInput->m_viewYaw = m_yaw;

        chickenInput->m_resetCount =
          GetNetworkTransformComponentController()->GetResetCount();
    }

    void ChickenMovementComponentController::ProcessInput(
        Multiplayer::NetworkInput& input,
        [[maybe_unused]] float deltaTime)
    {
        auto chickenInput = input.FindComponentInput<
            ChickenMovementComponentNetworkInput>();
        if (chickenInput->m_resetCount !=
          GetNetworkTransformComponentController()->GetResetCount())
        {
            return;
        }

        UpdateRotation(chickenInput);
        UpdateVelocity(chickenInput);

        GetNetworkCharacterComponentController()->
            TryMoveWithVelocity(GetVelocity(), deltaTime);
    }

    void ChickenMovementComponentController::OnPressed(float value)
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

    void ChickenMovementComponentController::OnHeld(float value)
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

    void ChickenMovementComponentController::OnReleased(float value)
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

    void ChickenMovementComponentController::UpdateRotation(
        const ChickenMovementComponentNetworkInput* input)
    {
        AZ::TransformInterface* t = GetEntity()->GetTransform();

        float currentHeading = t->GetWorldRotationQuaternion().
            GetEulerRadians().GetZ();
        currentHeading += input->m_viewYaw * GetTurnSpeed();
        AZ::Quaternion q =
            AZ::Quaternion::CreateRotationZ(currentHeading);

        t->SetWorldRotationQuaternion(q);
    }

    void ChickenMovementComponentController::UpdateVelocity(
        const ChickenMovementComponentNetworkInput* input)
    {
        const float currentHeading = GetEntity()->GetTransform()->
            GetWorldRotationQuaternion().GetEulerRadians().GetZ();

        const AZ::Vector3 fwd = AZ::Vector3::CreateAxisY(
            input->m_forwardAxis);
        const AZ::Vector3 strafe = AZ::Vector3::CreateAxisX(
            input->m_strafeAxis);
        AZ::Vector3 combined = fwd + strafe;
        if (combined.GetLength() > 1.f)
        {
            combined.Normalize();
        }
        SetVelocity(AZ::Quaternion::CreateRotationZ(currentHeading).
            TransformVector(combined) * GetWalkSpeed() +
            AZ::Vector3::CreateAxisZ(GetGravity()));
    }
} // namespace MyGem
