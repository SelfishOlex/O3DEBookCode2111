
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace WindowPosition
{
    class WindowPositionRequests
    {
    public:
        AZ_RTTI(WindowPositionRequests, "{83a04ef1-78e3-4dc9-8d7e-c502d36d0694}");
        virtual ~WindowPositionRequests() = default;
        // Put your public methods here
    };
    
    class WindowPositionBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using WindowPositionRequestBus = AZ::EBus<WindowPositionRequests, WindowPositionBusTraits>;
    using WindowPositionInterface = AZ::Interface<WindowPositionRequests>;

} // namespace WindowPosition
