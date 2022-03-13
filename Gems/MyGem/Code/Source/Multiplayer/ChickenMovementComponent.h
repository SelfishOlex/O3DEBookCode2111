#pragma once
#include <Source/AutoGen/ChickenMovementComponent.AutoComponent.h>
#include <StartingPointInput/InputEventNotificationBus.h>

namespace MyGem
{
    const StartingPointInput::InputEventNotificationId
        MoveFwdEventId("move forward");
    const StartingPointInput::InputEventNotificationId
        MoveRightEventId("move right");
    const StartingPointInput::InputEventNotificationId
        RotateYawEventId("rotate yaw");

    class ChickenMovementComponentController
        : public ChickenMovementComponentControllerBase
        , public StartingPointInput::
        InputEventNotificationBus::MultiHandler
    {
    public:
        ChickenMovementComponentController(
            ChickenMovementComponent& parent);

        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override;

        //! Common input creation logic for the NetworkInput.
        //! Fill out the input struct and the MultiplayerInputDriver
        //! will send the input data over the network to ensure
        //! it's processed.
        //! @param input  input structure which to store input data
        //!               for sending to the authority
        //! @param deltaTime amount of time to integrate
        //!                  the provided inputs over
        void CreateInput(
            Multiplayer::NetworkInput& input,
            float deltaTime) override;

        //! Common input processing logic for the NetworkInput.
        //! @param input  input structure to process
        //! @param deltaTime amount of time to integrate the
        //!                  provided inputs over
        void ProcessInput(
            Multiplayer::NetworkInput& input,
            float deltaTime) override;

        // AZ::InputEventNotificationBus interface
        void OnPressed(float value) override;
        void OnReleased(float value) override;
        void OnHeld(float value) override;

    protected:
        void UpdateRotation(
            const ChickenMovementComponentNetworkInput* input);
        void UpdateVelocity(
            const ChickenMovementComponentNetworkInput* input);

        float m_forward = 0;
        float m_strafe = 0;
        float m_yaw = 0;

        AZ::Vector3 m_velocity = AZ::Vector3::CreateZero();
    };
} // namespace MyGem
