#pragma once
#include <ChickenControllerComponent.h>
#include <GoalDetectorComponent.h>
#include <MyGemSystemComponent.h>
#include <UiScoreComponent.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

namespace MyGem
{
    class MyGemModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(MyGemModuleInterface, "{c3adc159-98b4-4a2e-9029-06f2a4ed0dfb}", AZ::Module);
        AZ_CLASS_ALLOCATOR(MyGemModuleInterface, AZ::SystemAllocator, 0);

        MyGemModuleInterface()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                MyGemSystemComponent::CreateDescriptor(),
                ChickenControllerComponent::CreateDescriptor(),
                GoalDetectorComponent::CreateDescriptor(),
                UiScoreComponent::CreateDescriptor(),
                });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyGemSystemComponent>(),
            };
        }
    };
}// namespace MyGem
