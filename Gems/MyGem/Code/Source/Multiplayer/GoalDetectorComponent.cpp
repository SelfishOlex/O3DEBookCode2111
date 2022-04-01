#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <Multiplayer/GoalDetectorComponent.h>
#include <MyGem/BallSpawnerBus.h>
#include <MyGem/UiScoreBus.h>
#include <Source/AutoGen/BallComponent.AutoComponent.h>

namespace MyGem
{
    GoalDetectorComponent::GoalDetectorComponent()
        : m_scoreChanged([this](int newScore)
        {
            OnScoreChanged(newScore);
        }) {}

    void GoalDetectorComponent::OnScoreChanged(int newScore)
    {
        UiScoreNotificationBus::Broadcast(
            &UiScoreNotificationBus::Events::OnTeamScoreChanged,
            GetTeam(), newScore);
    }

    void GoalDetectorComponent::Reflect(AZ::ReflectContext* rc)
    {
        auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
        if (sc)
        {
            sc->Class<GoalDetectorComponent,
                GoalDetectorComponentBase>()->Version(1);
        }
        GoalDetectorComponentBase::Reflect(rc);

        if (auto bc = azrtti_cast<AZ::BehaviorContext*>(rc))
        {
            bc->EBus<UiScoreNotificationBus>("ScoreNotificationBus")
                ->Handler<ScoreNotificationHandler>();
        }
    }

    void GoalDetectorComponent::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        ScoreAddEvent(m_scoreChanged);
    }

    // Controller
    GoalDetectorComponentController::GoalDetectorComponentController(
        GoalDetectorComponent& parent)
        : GoalDetectorComponentControllerBase(parent)
        , m_trigger([this](
            AzPhysics::SceneHandle,
            const AzPhysics::TriggerEventList& tel)
            {
                OnTriggerEvents(tel);
            }) {}

    void GoalDetectorComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        auto* si = AZ::Interface<AzPhysics::SceneInterface>::Get();
        if (si != nullptr)
        {
            AzPhysics::SceneHandle sh = si->GetSceneHandle(
                AzPhysics::DefaultPhysicsSceneName);
            si->RegisterSceneTriggersEventHandler(sh, m_trigger);
        }
    }

    void GoalDetectorComponentController::OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel)
    {
        const AZ::EntityId me = GetEntity()->GetId();

        using namespace AzPhysics;
        for (const TriggerEvent& te : tel)
        {
            if (te.m_triggerBody &&
                te.m_triggerBody->GetEntityId() == me)
            {
                if (te.m_type == TriggerEvent::Type::Enter)
                {
                    BallSpawnerRequestBus::Broadcast(
                      &BallSpawnerRequestBus::Events::RespawnBall);
                    ModifyScore()++;
                    break;
                }
            }
        }
    }
} // namespace MyGem
