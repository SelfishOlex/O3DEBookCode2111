
#include <AzCore/Serialization/SerializeContext.h>
#include <MyGemEditorSystemComponent.h>

namespace MyGem
{
    void MyGemEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MyGemEditorSystemComponent, MyGemSystemComponent>()
                ->Version(0);
        }
    }

    void MyGemEditorSystemComponent::Activate()
    {
        MyGemSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void MyGemEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        MyGemSystemComponent::Deactivate();
    }

} // namespace MyGem
