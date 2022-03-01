#include "OscillatorComponent.h"
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Component/TransformBus.h>

using namespace MyProject;

void OscillatorComponent::Activate()
{
    // We must connect, otherwise OnTick() will never be called.
    // Forgetting this call is the common error in O3DE!
    AZ::TickBus::Handler::BusConnect();
}

void OscillatorComponent::Deactivate()
{
    // good practice on cleanup to disconnect
    AZ::TickBus::Handler::BusDisconnect();
}

void OscillatorComponent::OnTick(float dt, AZ::ScriptTimePoint)
{
    m_currentTime += dt;

    // get current position
    AZ::Vector3 position;
    AZ::TransformBus::EventResult(position, GetEntityId(),
        &AZ::TransformBus::Events::GetWorldTranslation);

    // the amount of change per tick
    const float change = (dt / m_period) * m_amplitude;

    // move up during the first half of the period
    if (m_currentTime < m_period / 2)
    {
        position.SetZ(position.GetZ() + change);
        AZ::TransformBus::Event(GetEntityId(),
            &AZ::TransformBus::Events::SetWorldTranslation,
            position);
    }
    // move down during the second half of the period
    else if (m_currentTime < m_period)
    {
        position.SetZ(position.GetZ() - change);
        AZ::TransformBus::Event(GetEntityId(),
            &AZ::TransformBus::Events::SetWorldTranslation,
            position);
    }
    else // reset the time to start the next cycle
    {
        m_currentTime = 0;
    }
}

void OscillatorComponent::Reflect(AZ::ReflectContext* reflection)
{
    auto sc = azrtti_cast<AZ::SerializeContext*>(reflection);
    if (!sc) return;
    sc->Class<OscillatorComponent, Component>()
        ->Version(1);

    AZ::EditContext* ec = sc->GetEditContext();
    if (!ec) return;
    using namespace AZ::Edit::Attributes;
    // reflection of this component for O3DE Editor
    ec->Class<OscillatorComponent>("Oscillator Component",
        "[oscillates the entity]")
        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
        ->Attribute(AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
        ->Attribute(Category, "My Project");
}

void OscillatorComponent::GetRequiredServices(
    AZ::ComponentDescriptor::DependencyArrayType& req)
{
    // OscillatorComponent requires TransformComponent
    req.push_back(AZ_CRC_CE("TransformService"));
}