#include <GoalDetectorComponent.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <AzFramework/Physics/RigidBodyBus.h>
#include <MyGem/UiScoreBus.h>

namespace MyGem
{
    void GoalDetectorComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<GoalDetectorComponent, AZ::Component>()
              ->Field("Team", &GoalDetectorComponent::m_team)
              ->Field("Ball", &GoalDetectorComponent::m_ball)
              ->Field("Respawn", &GoalDetectorComponent::m_reset)
              ->Version(1);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                ec->Class<GoalDetectorComponent>(
                    "Goal Detector",
                    "[Detects when a goal is scored]")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(
                        Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("Game"))
                    ->DataElement(0, &GoalDetectorComponent::m_team,
                        "Team", "Which team is this goal line for?")
                    ->DataElement(0, &GoalDetectorComponent::m_ball,
                        "Ball", "Ball entity")
                    ->DataElement(0, &GoalDetectorComponent::m_reset,
                        "Respawn", "where to put the ball after")
                ;
            }
        }

        if (auto bc = azrtti_cast<AZ::BehaviorContext*>(rc))
        {
            bc->EBus<UiScoreNotificationBus>("ScoreNotificationBus")
                ->Handler<ScoreNotificationHandler>();
        }
    }

    GoalDetectorComponent::GoalDetectorComponent()
        : m_trigger([this](
            AzPhysics::SceneHandle,
            const AzPhysics::TriggerEventList& tel)
        {
            OnTriggerEvents(tel);
        })
    {
    }

    void GoalDetectorComponent::Activate()
    {
        auto* si = AZ::Interface<AzPhysics::SceneInterface>::Get();
        if (si != nullptr)
        {
            AzPhysics::SceneHandle sh = si->GetSceneHandle(
                AzPhysics::DefaultPhysicsSceneName);
            si->RegisterSceneTriggersEventHandler(sh, m_trigger);
        }
    }

    void GoalDetectorComponent::OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel)
    {
        using namespace AzPhysics;
        for (const TriggerEvent& te : tel)
        {
            if (te.m_triggerBody &&
                te.m_triggerBody->GetEntityId() == GetEntityId())
            {
                if (te.m_type == TriggerEvent::Type::Enter)
                {
                    AZ::Vector3 respawnLocation = GetRespawnPoint();
                    RespawnBall(respawnLocation);
                    UpdateUi();
                }
            }
        }
    }

    AZ::Vector3 GoalDetectorComponent::GetRespawnPoint() const
    {
        AZ::Vector3 respawnLocation = AZ::Vector3::CreateZero();
        AZ::TransformBus::EventResult(respawnLocation, m_reset,
            &AZ::TransformBus::Events::GetWorldTranslation);
        return respawnLocation;
    }

    void GoalDetectorComponent::RespawnBall(const AZ::Vector3& v)
    {
        Physics::RigidBodyRequestBus::Event(m_ball,
            &Physics::RigidBodyRequestBus::Events::DisablePhysics);
        AZ::TransformBus::Event(m_ball,
            &AZ::TransformBus::Events::SetWorldTranslation, v);
        Physics::RigidBodyRequestBus::Event(m_ball,
            &Physics::RigidBodyRequestBus::Events::EnablePhysics);
    }

    void GoalDetectorComponent::UpdateUi()
    {
        UiScoreNotificationBus::Broadcast(
            &UiScoreNotificationBus::Events::OnTeamScored, m_team);
    }
} // namespace MyGem
