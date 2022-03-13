#pragma once
#include <Source/AutoGen/BallComponent.AutoComponent.h>

namespace MyGem
{
    class BallComponentController
        : public BallComponentControllerBase
    {
    public:
        BallComponentController(BallComponent& parent);
        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override{}
    };
}