#pragma once
#include <ChickenAnimationComponent.h>
#include <ChickenControllerComponent.h>
#include <ChickenSpawnComponent.h>
#include <GoalDetectorComponent.h>
#include <KickingComponent.h>
#include <MyGemSystemComponent.h>
#include <UiScoreComponent.h>
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <Source/AutoGen/AutoComponentTypes.h>

namespace MyGem
{
    class MyGemModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(MyGemModuleInterface,
            "{c3adc159-98b4-4a2e-9029-06f2a4ed0dfb}", AZ::Module);
        AZ_CLASS_ALLOCATOR(MyGemModuleInterface,
            AZ::SystemAllocator, 0);

        MyGemModuleInterface()
        {
            m_descriptors.insert(m_descriptors.end(), {
                MyGemSystemComponent::CreateDescriptor(),
                ChickenControllerComponent::CreateDescriptor(),
                GoalDetectorComponent::CreateDescriptor(),
                UiScoreComponent::CreateDescriptor(),
                KickingComponent::CreateDescriptor(),
                ChickenAnimationComponent::CreateDescriptor(),
                ChickenSpawnComponent::CreateDescriptor(),
                });

            //< Register multiplayer components
            CreateComponentDescriptors(m_descriptors);
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList
            GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyGemSystemComponent>(),
            };
        }
    };
}// namespace MyGem
