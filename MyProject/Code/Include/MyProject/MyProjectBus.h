
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace MyProject
{
    class MyProjectRequests
    {
    public:
        AZ_RTTI(MyProjectRequests, "{68f129d3-3d9b-4f28-93cf-5268bf846899}");
        virtual ~MyProjectRequests() = default;
        // Put your public methods here
    };
    
    class MyProjectBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using MyProjectRequestBus = AZ::EBus<MyProjectRequests, MyProjectBusTraits>;
    using MyProjectInterface = AZ::Interface<MyProjectRequests>;

} // namespace MyProject
