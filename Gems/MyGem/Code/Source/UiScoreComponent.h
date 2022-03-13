#pragma once
#include <AzCore/Component/Component.h>
#include <MyGem/UiScoreBus.h>

namespace MyGem
{
    class UiScoreComponent
        : public AZ::Component
        , public UiScoreNotificationBus::Handler
    {
    public:
        AZ_COMPONENT(UiScoreComponent,
            "{49b2e5e8-e028-48b1-bc69-82c73b32422b}");

        static void Reflect(AZ::ReflectContext* rc);

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // UiScoreNotificationBus interface
        void OnTeamScoreChanged(int team, int score) override;

    private:
        int m_teams[2] = { 0, 0 };
    };
} // namespace MyGem
