#pragma once
#include <AzCore/Component/ComponentBus.h>

namespace MyGem
{
    class ChickenNotifications
        : public AZ::ComponentBus
    {
    public:
        virtual void OnChickenSpeedChanged(
            [[maybe_unused]] float speed) {}
        virtual void OnChickenCreated(
            [[maybe_unused]] AZ::Entity* e) {}
    };

    using ChickenNotificationBus = AZ::EBus<ChickenNotifications>;
}
