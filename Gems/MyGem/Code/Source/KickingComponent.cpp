#include <KickingComponent.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <AzFramework/Physics/RigidBodyBus.h>

namespace MyGem
{
    void KickingComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<KickingComponent, AZ::Component>()
              ->Field("Ball", &KickingComponent::m_ball)
              ->Field("Kick force", &KickingComponent::m_kickForce)
              ->Version(1);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                ec->Class<KickingComponent>(
                    "Kicking",
                    "[Kicking the ball when it comes close]")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(
                        Attributes::AppearsInAddComponentMenu,
                            AZ_CRC_CE("Game"))
                    ->DataElement(0, &KickingComponent::m_ball,
                        "Ball", "Ball entity")
                    ->DataElement(0, &KickingComponent::m_kickForce,
                        "Kick force", "impulse strength")
                ;
            }
        }
    }

    KickingComponent::KickingComponent()
        : m_trigger([this](
            AzPhysics::SceneHandle,
            const AzPhysics::TriggerEventList& tel)
        {
            OnTriggerEvents(tel);
        })
    {
    }

    void KickingComponent::Activate()
    {
        auto* si = AZ::Interface<AzPhysics::SceneInterface>::Get();
        if (si != nullptr)
        {
            AzPhysics::SceneHandle sh = si->GetSceneHandle(
                AzPhysics::DefaultPhysicsSceneName);
            si->RegisterSceneTriggersEventHandler(sh, m_trigger);
        }
    }

    void KickingComponent::OnTriggerEvents(
        const AzPhysics::TriggerEventList& tel)
    {
        using namespace AzPhysics;
        for (const TriggerEvent& te : tel)
        {
            if (te.m_triggerBody &&
                te.m_triggerBody->GetEntityId() == GetEntityId())
            {
                if (te.m_otherBody->GetEntityId() == m_ball &&
                    te.m_type == TriggerEvent::Type::Enter)
                {
                    KickBall();
                }
            }
        }
    }

    void KickingComponent::KickBall()
    {
        AZ::Vector3 impulse = GetBallPosition() - GetSelfPosition();

        impulse.Normalize();
        impulse *= m_kickForce;

        AddImpulseToBall(impulse);
    }

    AZ::Vector3 KickingComponent::GetBallPosition() const
    {
        AZ::Vector3 ballPosition = AZ::Vector3::CreateZero();
        AZ::TransformBus::EventResult(ballPosition, m_ball,
            &AZ::TransformBus::Events::GetWorldTranslation);
        return ballPosition;
    }

    AZ::Vector3 KickingComponent::GetSelfPosition() const
    {
        return GetEntity()->GetTransform()->
            GetWorldTM().GetTranslation();
    }

    void KickingComponent::AddImpulseToBall(const AZ::Vector3& v)
    {
        Physics::RigidBodyRequestBus::Event(m_ball,
          &Physics::RigidBodyRequestBus::Events::ApplyLinearImpulse,
            v);
    }
} // namespace MyGem
