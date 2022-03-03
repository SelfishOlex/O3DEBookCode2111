
#pragma once

#include <WindowPositionSystemComponent.h>

#include <AzToolsFramework/Entity/EditorEntityContextBus.h>

namespace WindowPosition
{
    /// System component for WindowPosition editor
    class WindowPositionEditorSystemComponent
        : public WindowPositionSystemComponent
        , private AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = WindowPositionSystemComponent;
    public:
        AZ_COMPONENT(WindowPositionEditorSystemComponent, "{ee291ab5-eb3c-43d5-a580-d9cc34f3e0ef}", BaseSystemComponent);
        static void Reflect(AZ::ReflectContext* context);

        WindowPositionEditorSystemComponent();
        ~WindowPositionEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace WindowPosition
