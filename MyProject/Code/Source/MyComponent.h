#pragma once
#include <AzCore/Component/Component.h>

namespace MyProject
{
    // An example of the simplest O3DE component
    class MyComponent : public AZ::Component
    {
    public:
        AZ_COMPONENT(MyComponent,
            "{4b589f6b-79f3-47b6-b730-aad0871d5f8f}");

        // AZ::Component overrides
        void Activate() override {}
        void Deactivate() override {}

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* reflection);
    };
}