
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

    MyGemEditorSystemComponent::MyGemEditorSystemComponent() = default;

    MyGemEditorSystemComponent::~MyGemEditorSystemComponent() = default;

    void MyGemEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("MyGemEditorService"));
    }

    void MyGemEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("MyGemEditorService"));
    }

    void MyGemEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void MyGemEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
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
