
#pragma once

#include <MyGemSystemComponent.h>

#include <AzToolsFramework/Entity/EditorEntityContextBus.h>

namespace MyGem
{
    /// System component for MyGem editor
    class MyGemEditorSystemComponent
        : public MyGemSystemComponent
        , private AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = MyGemSystemComponent;
    public:
        AZ_COMPONENT(MyGemEditorSystemComponent, "{89ad59bd-c4fd-4819-90fc-bd8a358d6255}", BaseSystemComponent);
        static void Reflect(AZ::ReflectContext* context);

        MyGemEditorSystemComponent();
        ~MyGemEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace MyGem
