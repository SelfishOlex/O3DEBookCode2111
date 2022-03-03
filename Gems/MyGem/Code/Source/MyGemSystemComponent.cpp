
#include <MyGemSystemComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace MyGem
{
    void MyGemSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<MyGemSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<MyGemSystemComponent>("MyGem", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void MyGemSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("MyGemService"));
    }

    void MyGemSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("MyGemService"));
    }

    void MyGemSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MyGemSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    MyGemSystemComponent::MyGemSystemComponent()
    {
        if (MyGemInterface::Get() == nullptr)
        {
            MyGemInterface::Register(this);
        }
    }

    MyGemSystemComponent::~MyGemSystemComponent()
    {
        if (MyGemInterface::Get() == this)
        {
            MyGemInterface::Unregister(this);
        }
    }

    void MyGemSystemComponent::Init()
    {
    }

    void MyGemSystemComponent::Activate()
    {
        MyGemRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void MyGemSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        MyGemRequestBus::Handler::BusDisconnect();
    }

    void MyGemSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace MyGem
