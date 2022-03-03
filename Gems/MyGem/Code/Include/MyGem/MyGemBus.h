
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace MyGem
{
    class MyGemRequests
    {
    public:
        AZ_RTTI(MyGemRequests, "{45ec313a-31a7-41ca-9e19-0f3f9351e328}");
        virtual ~MyGemRequests() = default;
        // Put your public methods here
    };
    
    class MyGemBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using MyGemRequestBus = AZ::EBus<MyGemRequests, MyGemBusTraits>;
    using MyGemInterface = AZ::Interface<MyGemRequests>;

} // namespace MyGem
