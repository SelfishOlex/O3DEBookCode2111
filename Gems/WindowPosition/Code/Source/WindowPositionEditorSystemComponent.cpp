
#include <AzCore/Serialization/SerializeContext.h>
#include <WindowPositionEditorSystemComponent.h>

namespace WindowPosition
{
    void WindowPositionEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<WindowPositionEditorSystemComponent, WindowPositionSystemComponent>()
                ->Version(0);
        }
    }

    WindowPositionEditorSystemComponent::WindowPositionEditorSystemComponent() = default;

    WindowPositionEditorSystemComponent::~WindowPositionEditorSystemComponent() = default;

    void WindowPositionEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("WindowPositionEditorService"));
    }

    void WindowPositionEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("WindowPositionEditorService"));
    }

    void WindowPositionEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void WindowPositionEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void WindowPositionEditorSystemComponent::Activate()
    {
        WindowPositionSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void WindowPositionEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        WindowPositionSystemComponent::Deactivate();
    }

} // namespace WindowPosition
