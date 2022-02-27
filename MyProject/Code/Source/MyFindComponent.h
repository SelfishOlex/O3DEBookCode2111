#pragma once
#include <AzCore/Component/Component.h>

namespace MyProject
{
    // An example of the simplest O3DE component
    class MyFindComponent : public AZ::Component
    {
    public:
        AZ_COMPONENT(MyFindComponent,
            "{FE4F2E82-8E03-48EC-A967-559705597040}");

        static void GetRequiredServices(
            AZ::ComponentDescriptor::DependencyArrayType& required)
        {
            required.push_back(AZ_CRC_CE("TransformService"));
        }

        // AZ::Component overrides
        void Activate() override;
        void Deactivate() override {}

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* rc);
    };
}