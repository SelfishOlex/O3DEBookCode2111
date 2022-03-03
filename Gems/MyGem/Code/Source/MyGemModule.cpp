

#include <MyGemModuleInterface.h>
#include <MyGemSystemComponent.h>

namespace MyGem
{
    class MyGemModule
        : public MyGemModuleInterface
    {
    public:
        AZ_RTTI(MyGemModule, "{27e66066-d995-40df-95c9-d478a06c0c61}", MyGemModuleInterface);
        AZ_CLASS_ALLOCATOR(MyGemModule, AZ::SystemAllocator, 0);
    };
}// namespace MyGem

AZ_DECLARE_MODULE_CLASS(Gem_MyGem, MyGem::MyGemModule)
