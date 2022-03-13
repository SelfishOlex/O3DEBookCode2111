#pragma once
#include <AzCore/Component/ComponentBus.h>
namespace MyGem
{
    class BallNotifications
        : public AZ::ComponentBus
    {
    public:
        virtual void OnBallSpawned(AZ::Entity* ballEntity) = 0;
    };

    using BallNotificationBus = AZ::EBus<BallNotifications>;
}
