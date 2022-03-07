#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace MyGem
{
    class UiScoreNotifications
        : public AZ::ComponentBus
    {
    public:
        virtual void OnTeamScored(int team) = 0;
    };

    using UiScoreNotificationBus = AZ::EBus<UiScoreNotifications>;
}
