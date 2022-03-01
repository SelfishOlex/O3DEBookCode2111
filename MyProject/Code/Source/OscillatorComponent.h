#pragma once
#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>

namespace MyProject
{
    // An example of singing up to an Ebus, TickBus in this case
    class OscillatorComponent
        : public AZ::Component
        , public AZ::TickBus::Handler // for ticking events
    {
    public:
        // be sure this guid is unique, avoid copy-paste errors!
        AZ_COMPONENT(OscillatorComponent,
            "{302AE5A0-F7C4-4319-8023-B1ADF53E1E72}");

    protected:
        // AZ::Component overrides
        void Activate() override;
        void Deactivate() override;

        // AZ::TickBus overrides
        void OnTick(float dt, AZ::ScriptTimePoint) override;

        // Provide runtime reflection, if any
        static void Reflect(AZ::ReflectContext* reflection);

        // what other components does this component require?
        static void GetRequiredServices(
            AZ::ComponentDescriptor::DependencyArrayType& req);

    private:
        float m_period = 3.f;
        float m_currentTime = 0.f;
        float m_amplitude = 10.f;
    };
}