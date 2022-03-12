#pragma once
#include <Source/AutoGen/ChickenComponent.AutoComponent.h>

namespace MyGem
{
    class ChickenComponentController
        : public ChickenComponentControllerBase
    {
    public:
        ChickenComponentController(ChickenComponent& parent);

        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override {}
    };
}