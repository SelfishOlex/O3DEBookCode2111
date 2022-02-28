#pragma once
#include <AzCore/Component/Component.h>
#include <MyProject/MyInterface.h>

namespace MyProject
{
    // An example of a level component with AZ::Interface
    class MyLevelComponent
        : public AZ::Component
        , public AZ::Interface<MyInterface>::Registrar
    {
    public:
        AZ_COMPONENT(MyLevelComponent,
            "{69C64F9C-4C35-4612-9B3B-85FEBCC06FDB}");
        
        // AZ::Component overrides
        void Activate() override {}
        void Deactivate() override {}

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* rc);

        // MyInterface
        int GetMyInteger() override { return 42; }
    };
}
