#include <UiScoreComponent.h>
#include <AzCore/Serialization/EditContext.h>
#include <LyShine/Bus/UiTextBus.h>

namespace MyGem
{
    void UiScoreComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<UiScoreComponent, AZ::Component>()
              ->Version(1);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                ec->Class<UiScoreComponent>(
                    "Ui Score Component",
                    "[Updates score text]")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(
                        Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("UI"));
            }
        }
    }

    void UiScoreComponent::Activate()
    {
        UiScoreNotificationBus::Handler::BusConnect(GetEntityId());
    }

    void UiScoreComponent::Deactivate()
    {
        UiScoreNotificationBus::Handler::BusDisconnect();
    }

    void UiScoreComponent::OnTeamScoreChanged(int team, int score)
    {
        if (team >= 0 && team <= 1)
        {
            m_teams[team] = score;
            char buffer[10];
            azsnprintf(buffer, 10,
                "%d : %d", m_teams[0], m_teams[1]);
            UiTextBus::Event(GetEntityId(),
                &UiTextBus::Events::SetText, AZStd::string(buffer));
        }
    }
} // namespace MyGem
