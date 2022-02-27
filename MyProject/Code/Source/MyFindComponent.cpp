#include "MyFindComponent.h"
#include <AzCore/Component/Entity.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Components/TransformComponent.h>

using namespace MyProject;

void MyFindComponent::Activate()
{
    AZ::Entity* e = GetEntity();

    using namespace AzFramework;
    TransformComponent* tc = e->FindComponent<TransformComponent>();
    if (tc)
    {
        AZ::Transform t = tc->GetWorldTM();
        AZ::Vector3 p = t.GetTranslation();
        AZ_Printf("MyFind", "activated at %f %f %f",
            p.GetX(), p.GetY(), p.GetZ() );
    }
}

void MyFindComponent::Reflect(AZ::ReflectContext* rc)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
    if (!sc) return;

    sc->Class<MyFindComponent, Component>()
        ->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;

    using namespace AZ::Edit::Attributes;
    // reflection of this component for O3DE Editor
    ec->Class<MyFindComponent>("Find Component Example",
        "[Communicates using FindComponent]")
      ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu, AZ_CRC("Game"))
        ->Attribute(Category, "My Project");
}
