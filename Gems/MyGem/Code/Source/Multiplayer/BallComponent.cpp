#include <Multiplayer/BallComponent.h>
#include <MyGem/BallBus.h>

namespace MyGem
{
    BallComponentController::BallComponentController(
            BallComponent& parent)
        : BallComponentControllerBase(parent) {}

    void BallComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        BallNotificationBus::Broadcast(
            &BallNotificationBus::Events::OnBallSpawned,
            GetEntity());
    }
}
