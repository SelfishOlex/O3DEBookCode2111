#include <MyGemSystemComponent.h>
#include <AzCore/Serialization/EditContext.h>
#include <Source/AutoGen/AutoComponentTypes.h>

namespace MyGem
{
    void MyGemSystemComponent::Reflect(AZ::ReflectContext* rc)
    {
        if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
        {
            sc->Class<MyGemSystemComponent, AZ::Component>()
                ->Version(0);

            if (AZ::EditContext* ec = sc->GetEditContext())
            {
                using namespace AZ::Edit;
                using namespace AZ::Edit::Attributes;
                ec->Class<MyGemSystemComponent>("MyGem", "")
                    ->ClassElement(ClassElements::EditorData, "")
                    ->Attribute(AppearsInAddComponentMenu, 
                        AZ_CRC("System"));
            }
        }
    }

    void MyGemSystemComponent::Activate()
    {
        // Register multiplayer components
        RegisterMultiplayerComponents();
    }
} // namespace MyGem
