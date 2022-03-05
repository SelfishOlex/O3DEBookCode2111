#pragma once
#include <AzCore/Component/Component.h>
#include <StartingPointInput/InputEventNotificationBus.h>

namespace MyGem
{
    const StartingPointInput::InputEventNotificationId MoveFwdEventId("move forward");
    
    class ChickenControllerComponent
        : public AZ::Component
        , public StartingPointInput::InputEventNotificationBus::MultiHandler
    {
    public:
        AZ_COMPONENT(ChickenControllerComponent, "{fe639d60-75c0-4e16-aa1a-0d44dbe6d339}");

        static void Reflect(AZ::ReflectContext* context);
        
        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // AZ::InputEventNotificationBus interface
        void OnPressed(float value) override;
        void OnReleased(float value) override;        
    };

} // namespace MyGem
