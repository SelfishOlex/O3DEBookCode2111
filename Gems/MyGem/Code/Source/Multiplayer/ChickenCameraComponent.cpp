#include <AzCore/Component/ComponentApplicationBus.h>
#include <AzFramework/Components/CameraBus.h>
#include <AzFramework/Components/TransformComponent.h>
#include <Multiplayer/ChickenCameraComponent.h>

namespace MyGem
{
    ChickenCameraComponentController::
        ChickenCameraComponentController(ChickenCameraComponent& p)
        : ChickenCameraComponentControllerBase(p) {}

    void ChickenCameraComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        if (IsAutonomous())
        {
            AZ::TickBus::Handler::BusConnect();
        }
    }

    void ChickenCameraComponentController::OnDeactivate(
        Multiplayer::EntityIsMigrating)
    {
        AZ::TickBus::Handler::BusDisconnect();
    }

    void ChickenCameraComponentController::OnTick(
        float, AZ::ScriptTimePoint)
    {
        if (!m_activeCameraEntity)
        {
            m_activeCameraEntity = GetActiveCamera();
            return;
        }

        AZ::Transform chicken =
            GetParent().GetTransformComponent()->GetWorldTM();
        AZ::Vector3 camera = chicken.GetTranslation() +
            chicken.GetRotation().TransformVector(GetCameraOffset());

        chicken.SetTranslation(camera);
        m_activeCameraEntity->GetTransform()->SetWorldTM(chicken);
    }

    int ChickenCameraComponentController::GetTickOrder()
    {
        return AZ::TICK_PRE_RENDER;
    }

    AZ::Entity* ChickenCameraComponentController::GetActiveCamera()
    {
        using namespace AZ;
        using namespace Camera;
        EntityId activeCameraId;
        CameraSystemRequestBus::BroadcastResult( activeCameraId,
            &CameraSystemRequestBus::Events::GetActiveCamera);

        auto ca = Interface<ComponentApplicationRequests>::Get();
        return ca->FindEntity(activeCameraId);
    }
}
