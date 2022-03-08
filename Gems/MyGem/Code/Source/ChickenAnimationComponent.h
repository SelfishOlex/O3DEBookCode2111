#pragma once
#include <AzCore/Component/Component.h>
#include <MyGem/ChickenBus.h>

namespace MyGem
{
    class ChickenAnimationComponent
        : public AZ::Component
        , public ChickenNotificationBus::Handler
    {
    public:
        AZ_COMPONENT(ChickenAnimationComponent,
            "{ED8B6A79-AA47-44B2-91B6-64A78439B037}");

        static void Reflect(AZ::ReflectContext* rc);

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // ChickenNotificationBus interface
        void OnChickenSpeedChanged(float s) override;

    private:
        AZ::EntityId m_actor;
    };
} // namespace MyGem
