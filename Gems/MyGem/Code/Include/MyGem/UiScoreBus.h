#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace MyGem
{
    class UiScoreNotifications
        : public AZ::ComponentBus
    {
    public:
        virtual void OnTeamScoreChanged(int team, int score) = 0;
    };

    using UiScoreNotificationBus = AZ::EBus<UiScoreNotifications>;

    class ScoreNotificationHandler
        : public UiScoreNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(ScoreNotificationHandler,
            "", AZ::SystemAllocator,
            OnTeamScoreChanged);

        void OnTeamScoreChanged(int team, int score) override
        {
            Call(FN_OnTeamScoreChanged, team, score);
        }
    };
}
