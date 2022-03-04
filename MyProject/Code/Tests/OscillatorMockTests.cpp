#include <OscillatorComponent.h>
#include <AzCore/Component/ComponentApplication.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>
#include <AzCore/UnitTest/TestTypes.h>
#include <AzTest/AzTest.h>

using namespace AZ;
using namespace AZStd;
using namespace MyProject;
using namespace ::testing;

/**
 * \brief Pretend to be a TransformComponent
 */
class MockTransformComponent
    : public AZ::Component
    , public AZ::TransformBus::Handler
{
public:    
    // be sure this guid is unique, avoid copy-paste errors!
    AZ_COMPONENT(MockTransformComponent,
        "{7E8087BD-46DA-4708-ADB0-08D7812CA49F}");

    // Just a mock object, no reflection necessary
    static void Reflect(ReflectContext*) {}

    // Mimic Transform component service
    static void GetProvidedServices(
            AZ::ComponentDescriptor::DependencyArrayType& req)
    {
        req.push_back(AZ_CRC("TransformService"));
    }

    // Mocking out pure virtual methods
    void Activate() override
    {
        AZ::TransformBus::Handler::BusConnect(GetEntityId());
    }
    void Deactivate() override
    {
        AZ::TransformBus::Handler::BusDisconnect();
    }

    // OscillatorComponent will be calling these methods
    MOCK_METHOD1(SetWorldTranslation, void (const AZ::Vector3&));
    MOCK_METHOD0(GetWorldTranslation, AZ::Vector3 ());

    // Unused methods but they are pure virtual in TransformBus
    MOCK_METHOD0(IsStaticTransform, bool ());
    MOCK_METHOD0(IsPositionInterpolated, bool ());
    MOCK_METHOD0(IsRotationInterpolated, bool ());
    MOCK_METHOD0(GetLocalTM, const Transform& ());
    MOCK_METHOD0(GetWorldTM, const Transform& ());
    MOCK_METHOD1(BindTransformChangedEventHandler,
        void(TransformChangedEvent::Handler&));
    MOCK_METHOD1(BindParentChangedEventHandler,
        void(ParentChangedEvent::Handler&));
    MOCK_METHOD1(BindChildChangedEventHandler,
        void(ChildChangedEvent::Handler&));
    MOCK_METHOD2(NotifyChildChangedEvent,
        void(ChildChangeType, EntityId));
};

class OscillatorMockTest
    : public ::UnitTest::AllocatorsFixture
{
    AZStd::unique_ptr<AZ::SerializeContext> m_sc;
    AZStd::unique_ptr<AZ::ComponentDescriptor> m_md;
    AZStd::unique_ptr<AZ::ComponentDescriptor> m_od;

protected:
    void SetUp() override
    {
        ::UnitTest::AllocatorsFixture::SetUp();

        // register components involved in testing
        m_sc = AZStd::make_unique<AZ::SerializeContext>();
        m_md.reset(MockTransformComponent::CreateDescriptor());
        m_md->Reflect(m_sc.get());
        m_od.reset(OscillatorComponent::CreateDescriptor());
        m_od->Reflect(m_sc.get());
    }

    void TearDown() override
    {
        m_md.reset();
        m_od.reset();
        m_sc.reset();

        ::UnitTest::AllocatorsFixture::TearDown();
    }

    // helper method
    void PopulateEntity(Entity& e)
    {
        // OscillatorComponent is the component we are testing
        e.CreateComponent<OscillatorComponent>();
        // We can mock out Transform and test the interaction
        mock = new NiceMock<MockTransformComponent>();
        e.AddComponent(mock);

        // Bring the entity online
        e.Init();
        e.Activate();
    }

    MockTransformComponent* mock = nullptr;
};

TEST_F(OscillatorMockTest, Calls_SetWorldTranslation)
{
    Entity e;
    PopulateEntity(e);

    // setup a return value for GetWorldTranslation()
    ON_CALL(*mock, GetWorldTranslation()).WillByDefault(
        Return(AZ::Vector3::CreateZero()));

    // expect SetWorldTranslation() to be called
    EXPECT_CALL(*mock, SetWorldTranslation(_)).Times(1);

    TickBus::Broadcast(&TickBus::Events::OnTick, 0.1f,
            ScriptTimePoint());
}