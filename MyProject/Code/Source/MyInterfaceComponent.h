#pragma once
#include <AzCore/Component/Component.h>

namespace MyProject
{
    // An example of using AZ::Interface
    class MyInterfaceComponent : public AZ::Component
    {
    public:
        AZ_COMPONENT(MyInterfaceComponent,
            "{F73AB7B7-4F19-42FD-9651-13167FD222A6}");
        
        // AZ::Component overrides
        void Activate() override;
        void Deactivate() override {}

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* rc);
    };
}