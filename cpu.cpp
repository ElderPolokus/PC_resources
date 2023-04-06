#include "cpu.h"
#include <windows.h>
#include <winternl.h>

cpu::cpu() {
    typedef NTSTATUS (NTAPI* pfNtQuerySystemInformation) (
            IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
            OUT PVOID SystemInformation,
            IN ULONG SystemInformationLength,
            OUT PULONG ReturnLength OPTIONAL
            );

        static pfNtQuerySystemInformation NtQuerySystemInformation = NULL;

        if(NtQuerySystemInformation == NULL)
        {
            HMODULE ntDLL = ::GetModuleHandleA("ntdll.dll");
            NtQuerySystemInformation = (pfNtQuerySystemInformation)GetProcAddress(ntDLL ,"NtQuerySystemInformation");
        }

        static SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION lastInfo = {0};
        SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION curInfo = {0};

        ULONG retsize;

        NtQuerySystemInformation(SystemProcessorPerformanceInformation, &curInfo, sizeof(curInfo), &retsize);

        double cpuUsage = -1;

        if(lastInfo.KernelTime.QuadPart != 0 || lastInfo.UserTime.QuadPart != 0)
            cpuUsage = 100.0 - double(curInfo.IdleTime.QuadPart - lastInfo.IdleTime.QuadPart) /
            double(curInfo.KernelTime.QuadPart - lastInfo.KernelTime.QuadPart + curInfo.UserTime.QuadPart - lastInfo.UserTime.QuadPart) * 100.0;

        lastInfo = curInfo;

        cpu_value_int = cpuUsage;
}
