#pragma once
#include <AzCore/Component/ComponentBus.h>
namespace MyGem
{
    class BallSpawnerRequests
        : public AZ::ComponentBus
    {
    public:
        virtual void RespawnBall() = 0;
    };

    using BallSpawnerRequestBus = AZ::EBus<BallSpawnerRequests>;
}
