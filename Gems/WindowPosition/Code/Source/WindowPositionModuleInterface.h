
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <WindowPositionSystemComponent.h>

namespace WindowPosition
{
    class WindowPositionModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(WindowPositionModuleInterface, "{7d4260df-ccee-4ccf-908c-3de94a8cee9e}", AZ::Module);
        AZ_CLASS_ALLOCATOR(WindowPositionModuleInterface, AZ::SystemAllocator, 0);

        WindowPositionModuleInterface()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                WindowPositionSystemComponent::CreateDescriptor(),
                });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<WindowPositionSystemComponent>(),
            };
        }
    };
}// namespace WindowPosition
