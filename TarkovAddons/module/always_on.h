#pragma once
#include "../il2cpp/Il2CppObjectInstance.h"
#include "../il2cpp/il2utils.h"

namespace always_on
{
    static inline Il2CppImage* assembly_csharp;

    inline void init()
    {
        // set assembly csharp image
        assembly_csharp = il2utils::resolve_image("Assembly-CSharp.dll");
    }
}
