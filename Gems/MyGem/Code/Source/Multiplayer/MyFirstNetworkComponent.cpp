#include <Multiplayer/MyFirstNetworkComponent.h>
#include <AzCore/Serialization/SerializeContext.h>

namespace MyGem
{
    void MyFirstNetworkComponent::Reflect(AZ::ReflectContext* rc)
    {
        auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
        if (sc)
        {
            sc->Class<MyFirstNetworkComponent,
                      MyFirstNetworkComponentBase>()
                ->Version(1);
        }
        MyFirstNetworkComponentBase::Reflect(rc);
    }

    void MyFirstNetworkComponent::OnInit()
    {
    }

    void MyFirstNetworkComponent::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        AZ_Printf(__FUNCTION__, "we are on entity %s",
            GetEntity()->GetName().c_str());
    }

    void MyFirstNetworkComponent::OnDeactivate(
        Multiplayer::EntityIsMigrating)
    {
    }

    MyFirstNetworkComponentController::
      MyFirstNetworkComponentController(MyFirstNetworkComponent& p)
        : MyFirstNetworkComponentControllerBase(p)
    {
    }

    void MyFirstNetworkComponentController::OnActivate(
        Multiplayer::EntityIsMigrating)
    {
        AZ_Printf(__FUNCTION__, "we are on entity %s",
            GetEntity()->GetName().c_str());
    }

    void MyFirstNetworkComponentController::OnDeactivate(
        Multiplayer::EntityIsMigrating)
    {
    }
}