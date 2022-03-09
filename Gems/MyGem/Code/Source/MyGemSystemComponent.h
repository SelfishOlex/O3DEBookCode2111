#pragma once
#include <AzCore/Component/Component.h>

namespace MyGem
{
    class MyGemSystemComponent
        : public AZ::Component
    {
    public:
        AZ_COMPONENT(MyGemSystemComponent,
            "{9514f56f-24b5-4159-85f4-19253f0a9d87}");

        static void Reflect(AZ::ReflectContext* context);

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override {}
    };
} // namespace MyGem
