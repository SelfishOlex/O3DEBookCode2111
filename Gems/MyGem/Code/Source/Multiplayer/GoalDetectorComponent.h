#pragma once
#include <AzCore/Component/Component.h>
#include <AzFramework/Physics/Common/PhysicsEvents.h>
#include <Source/AutoGen/GoalDetectorComponent.AutoComponent.h>

namespace MyGem
{
    class GoalDetectorComponent
        : public GoalDetectorComponentBase
    {
    public:
        AZ_MULTIPLAYER_COMPONENT(MyGem::GoalDetectorComponent,
            s_goalDetectorComponentConcreteUuid,
            MyGem::GoalDetectorComponentBase);

        GoalDetectorComponent();
        static void Reflect(AZ::ReflectContext* context);

        void OnInit() override {}
        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override{}

    private:
        AZ::Event<int>::Handler m_scoreChanged;
        void OnScoreChanged(int newScore);
    };

    class GoalDetectorComponentController
        : public GoalDetectorComponentControllerBase
    {
    public:
        GoalDetectorComponentController(GoalDetectorComponent& p);

        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override{}

    private:
        AzPhysics::SceneEvents::
            OnSceneTriggersEvent::Handler m_trigger;
        void OnTriggerEvents(
            const AzPhysics::TriggerEventList& tel);
    };
} // namespace MyGem
