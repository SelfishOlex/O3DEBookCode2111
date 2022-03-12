#pragma once
#include <Source/AutoGen/MyFirstNetworkComponent.AutoComponent.h>

namespace MyGem
{
    class MyFirstNetworkComponent
        : public MyFirstNetworkComponentBase
    {
    public:
        AZ_MULTIPLAYER_COMPONENT(MyGem::MyFirstNetworkComponent,
            s_myFirstNetworkComponentConcreteUuid,
            MyGem::MyFirstNetworkComponentBase);

        static void Reflect(AZ::ReflectContext* context);

        void OnInit() override;
        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override;

    protected:
    };

    class MyFirstNetworkComponentController
        : public MyFirstNetworkComponentControllerBase
    {
    public:
        MyFirstNetworkComponentController(
            MyFirstNetworkComponent& parent);

        void OnActivate(Multiplayer::EntityIsMigrating) override;
        void OnDeactivate(Multiplayer::EntityIsMigrating) override;

    protected:
    };
}