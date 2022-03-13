#include <Multiplayer/ChickenComponent.h>
#include <MyGem/ChickenBus.h>

namespace MyGem
{
    ChickenComponentController::
      ChickenComponentController(ChickenComponent& p)
        : ChickenComponentControllerBase(p) {}

    void ChickenComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        if (!IsAuthority()) return;

        ChickenNotificationBus::Broadcast(
            &ChickenNotificationBus::Events::OnChickenCreated,
                GetEntity(), GetTeam());
    }
}
