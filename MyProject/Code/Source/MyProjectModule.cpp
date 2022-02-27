
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

#include "MyComponent.h"
#include "MyFindComponent.h"
#include "MyProjectSystemComponent.h"

namespace MyProject
{
    class MyProjectModule
        : public AZ::Module
    {
    public:
        AZ_RTTI(MyProjectModule, "{4b67609b-b22c-4a71-9afe-3f9d10bcf5ac}", AZ::Module);
        AZ_CLASS_ALLOCATOR(MyProjectModule, AZ::SystemAllocator, 0);

        MyProjectModule()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), {
                MyProjectSystemComponent::CreateDescriptor(),
                MyComponent::CreateDescriptor(),
                MyFindComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<MyProjectSystemComponent>(),
            };
        }
    };
}// namespace MyProject

AZ_DECLARE_MODULE_CLASS(Gem_MyProject, MyProject::MyProjectModule)
