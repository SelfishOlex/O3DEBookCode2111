
#include <WindowPositionSystemComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace WindowPosition
{
    void WindowPositionSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<WindowPositionSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<WindowPositionSystemComponent>("WindowPosition", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void WindowPositionSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("WindowPositionService"));
    }

    void WindowPositionSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("WindowPositionService"));
    }

    void WindowPositionSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void WindowPositionSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    WindowPositionSystemComponent::WindowPositionSystemComponent()
    {
        if (WindowPositionInterface::Get() == nullptr)
        {
            WindowPositionInterface::Register(this);
        }
    }

    WindowPositionSystemComponent::~WindowPositionSystemComponent()
    {
        if (WindowPositionInterface::Get() == this)
        {
            WindowPositionInterface::Unregister(this);
        }
    }

    void WindowPositionSystemComponent::Init()
    {
    }

    void WindowPositionSystemComponent::Activate()
    {
        WindowPositionRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void WindowPositionSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        WindowPositionRequestBus::Handler::BusDisconnect();
    }

    void WindowPositionSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace WindowPosition
