#include <IAEngine/Physics/Physics.hpp>

namespace ia::iae
{
   

    VOID Physics::Initialize()
    {
    }

    VOID Physics::Terminate()
    {
    }

    VOID Physics::Update()
    {
    }

    Handle Physics::CreateStaticBody(IN iam::Vec3f position)
    {
        return INVALID_HANDLE;
    }

    Handle Physics::CreateDynamicBody(IN iam::Vec3f position)
    {
        return INVALID_HANDLE;
    }

    VOID Physics::AddBoxCollider(IN Handle body, IN iam::Vec3f size)
    {
    }

    iam::Vec3f Physics::GetBodyPosition(IN Handle body)
    {
        return {};
    }
} // namespace ia::iae