

#include <WindowPositionModuleInterface.h>
#include <WindowPositionSystemComponent.h>

namespace WindowPosition
{
    class WindowPositionModule
        : public WindowPositionModuleInterface
    {
    public:
        AZ_RTTI(WindowPositionModule, "{baf22a9a-6fb8-4a66-a53e-bc3bc8f8d44e}", WindowPositionModuleInterface);
        AZ_CLASS_ALLOCATOR(WindowPositionModule, AZ::SystemAllocator, 0);
    };
}// namespace WindowPosition

AZ_DECLARE_MODULE_CLASS(Gem_WindowPosition, WindowPosition::WindowPositionModule)
