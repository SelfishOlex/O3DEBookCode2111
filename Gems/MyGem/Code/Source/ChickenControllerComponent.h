#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Math/Vector3.h>
#include <StartingPointInput/InputEventNotificationBus.h>

namespace MyGem
{
    const StartingPointInput::InputEventNotificationId
        MoveFwdEventId("move forward");
    const StartingPointInput::InputEventNotificationId
        MoveRightEventId("move right");
    const StartingPointInput::InputEventNotificationId
        RotateYawEventId("rotate yaw");

    class ChickenInput
    {
    public:
        float m_forwardAxis = 0;
        float m_strafeAxis = 0;
        float m_viewYaw = 0;
    };

    class ChickenControllerComponent
        : public AZ::Component
        , public AZ::TickBus::Handler
        , public StartingPointInput::
            InputEventNotificationBus::MultiHandler
    {
    public:
        AZ_COMPONENT(ChickenControllerComponent,
            "{fe639d60-75c0-4e16-aa1a-0d44dbe6d339}");

        static void Reflect(AZ::ReflectContext* rc);

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // AZ::InputEventNotificationBus interface
        void OnPressed(float value) override;
        void OnReleased(float value) override;
        void OnHeld(float value) override;

        // TickBus interface
        void OnTick(float deltaTime, AZ::ScriptTimePoint) override;

    private:
        ChickenInput CreateInput();
        void ProcessInput(const ChickenInput& input);

        void UpdateRotation(const ChickenInput& input);
        void UpdateVelocity(const ChickenInput& input);
        AZ::Vector3 m_velocity = AZ::Vector3::CreateZero();

        float m_speed = 10.f;
        float m_turnSpeed = 1.f;

        float m_forward = 0.f;
        float m_strafe = 0.f;
        float m_yaw = 0.f;
    };

} // namespace MyGem
