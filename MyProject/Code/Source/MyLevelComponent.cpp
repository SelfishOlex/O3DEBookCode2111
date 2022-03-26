#include "MyLevelComponent.h"
#include <AzCore/Component/Entity.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzFramework/Components/TransformComponent.h>

using namespace MyProject;

void MyLevelComponent::Reflect(AZ::ReflectContext* rc)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(rc);
    if (!sc) return;

    sc->Class<MyLevelComponent, Component>()
        ->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;

    using namespace AZ::Edit::Attributes;
    // reflection of this component for O3DE Editor
    ec->Class<MyLevelComponent>("My Level Component",
        "[Communicates using AZ::Interface]")
      ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu, AZ_CRC_CE("Level"))
        ->Attribute(Category, "My Project");
}
