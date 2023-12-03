#include <windows.h>
#include <psapi.h>

#include "memory.h"

void InitASI()
{
    HMODULE modBase = GetModuleHandle(NULL);

    MODULEINFO modInfo;
    GetModuleInformation(GetCurrentProcess(), modBase, &modInfo, sizeof(modInfo));

    DWORD oldProtect;

    void * fps_writer = ScanBasic("\xf3\x00\x00\x00\x00\x00\x00\x00\x00\x48\x8d\x8c\x24\xa0\x00\x00\x00\xf3\x44\x0f\x5e\xd0", "x????????xxxxxxxxxxxxx", (void *)modBase, modInfo.SizeOfImage);
    if (!fps_writer)
        return;

    VirtualProtect(fps_writer, 9, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(fps_writer, "\x90\x90\x90\x90\x90\x90\x90\x90\x90", 9);
    VirtualProtect(fps_writer, 9, oldProtect, &oldProtect);
}

static LONG InitCount = 0;
__declspec(dllexport) void InitializeASI()
{
    if ( _InterlockedCompareExchange( &InitCount, 1, 0 ) != 0 ) return;
    InitASI();
}
