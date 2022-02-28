#pragma once
#include <AzCore/RTTI/RTTI.h>

namespace MyProject
{
    class MyInterface
    {
    public:
        AZ_RTTI(MyInterface, "{D477F807-6795-4A1B-A475-AFBCF0584A08}");
        virtual ~MyInterface() = default;

        virtual int GetMyInteger() = 0;
    };
}
