
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

#include "MyProjectSystemComponent.h"

namespace MyProject
{
    void MyProjectSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<MyProjectSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<MyProjectSystemComponent>("MyProject", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void MyProjectSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("MyProjectService"));
    }

    void MyProjectSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("MyProjectService"));
    }

    void MyProjectSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void MyProjectSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
    
    MyProjectSystemComponent::MyProjectSystemComponent()
    {
        if (MyProjectInterface::Get() == nullptr)
        {
            MyProjectInterface::Register(this);
        }
    }

    MyProjectSystemComponent::~MyProjectSystemComponent()
    {
        if (MyProjectInterface::Get() == this)
        {
            MyProjectInterface::Unregister(this);
        }
    }

    void MyProjectSystemComponent::Init()
    {
    }

    void MyProjectSystemComponent::Activate()
    {
        MyProjectRequestBus::Handler::BusConnect();
    }

    void MyProjectSystemComponent::Deactivate()
    {
        MyProjectRequestBus::Handler::BusDisconnect();
    }
}
