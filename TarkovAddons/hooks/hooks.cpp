#include "hooks.h"

#include <vector>

#include <detours/detours.h>

namespace hooks
{
    namespace
    {
        auto hook_log = std::vector<hook_data>();
    }

    void hook(PVOID target, PVOID hook, PVOID* original)
    {
        *original = target;
        DetourUpdateThread(GetCurrentThread());
        DetourTransactionBegin();
        DetourAttach(original, hook);
        DetourTransactionCommit();
        hook_log.push_back({hook, original});
    }

    void unhook(PVOID target, PVOID hook, PVOID* original)
    {
        *original = target;
        DetourUpdateThread(GetCurrentThread());
        DetourTransactionBegin();
        DetourDetach(original, hook);
        DetourTransactionCommit();
        int t = 0;
        for (int i = 0; i < hook_log.size(); ++i)
        {
            if (hook_log[i].original == original && hook_log[i].hook == hook)
            {
                t = i;
            }
        }
        hook_log.erase(hook_log.begin() + t);
    }

    void unhook_all()
    {
        for (auto log : hook_log)
        {
            DetourUpdateThread(GetCurrentThread());
            DetourTransactionBegin();
            DetourDetach(log.original, log.hook);
            DetourTransactionCommit();
        }
        hook_log.clear();
    }
}
