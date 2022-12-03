#pragma once
#include <iostream>
#include <windows.h>
#include <intrin.h>
#include <TlHelp32.h>
#include "xor.hpp"

namespace vmDetection {
	bool invalidTSC()
	{
		UINT64 timestampOne{ __rdtsc() };
		UINT64 timestampTwo{ __rdtsc() };
		return ((timestampTwo - timestampOne) > 500);
	}
	bool cpu_known_vm_vendors() 
	{
		int cpuInfo[4];
		__cpuid(cpuInfo, 1);

		if (!(cpuInfo[2] & (1 << 31)))
			return false;

		const auto queryVendorIdMagic{ 0x40000000 };
		constexpr int vendorIdLength{ 13 };
		char hyperVendorId[vendorIdLength];

		__cpuid(cpuInfo, queryVendorIdMagic);
		memcpy(hyperVendorId + 0, &cpuInfo[1], 4);
		memcpy(hyperVendorId + 4, &cpuInfo[2], 4);
		memcpy(hyperVendorId + 8, &cpuInfo[3], 4);
		hyperVendorId[12] = '\0';

		static const char* vendors[]{
		"KVMKVMKVM\0\0\0", // KVM 
		"Microsoft Hv",    // Microsoft Hyper-V or Windows Virtual PC */
		"VMwareVMware",    // VMware 
		"XenVMMXenVMM",    // Xen 
		"prl hyperv  ",    // Parallels
		"VBoxVBoxVBox"     // VirtualBox 
		};

		for (const auto& vendor : vendors)
		{
			if (!memcmp(vendor, hyperVendorId, vendorIdLength))
				return true;
		}

		return false;
	}
	bool isVM() {
		if (invalidTSC() && cpu_known_vm_vendors()) {

			return true;

		}
	}
} 

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

namespace AntiDebug {
	void bsod()
	{
		BOOLEAN bEnabled;
		ULONG uResp;
		LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
		LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
		pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
		pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
		NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
		NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
	}

	void DebuggerPresent()
	{
		if (IsDebuggerPresent())
		{
			bsod();
		}
	}
	DWORD_PTR FindProcessId2(const std::string processName)
	{
		PROCESSENTRY32 processInfo;
		processInfo.dwSize = sizeof(processInfo);

		HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		if (processesSnapshot == INVALID_HANDLE_VALUE)
			return 0;

		Process32First(processesSnapshot, &processInfo);
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}

		while (Process32Next(processesSnapshot, &processInfo))
		{
			if (!processName.compare(processInfo.szExeFile))
			{
				CloseHandle(processesSnapshot);
				return processInfo.th32ProcessID;
			}
		}

		CloseHandle(processesSnapshot);
		return 0;
	}
	void ScanProccessListForBlacklistedProcess()
	{
		if (FindProcessId2("ollydbg.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("ProcessHacker.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("tcpview.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("autoruns.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("autorunsc.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("filemon.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("procmon.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("regmon.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("procexp.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("idaq.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("idaq64.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("ImmunityDebugger.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("Wireshark.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("dumpcap.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("HookExplorer.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("ImportREC.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("PETools.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("LordPE.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("dumpcap.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("SysInspector.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("proc_analyzer.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("sysAnalyzer.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("sniff_hit.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("windbg.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("joeboxcontrol.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("Fiddler.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("joeboxserver.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("ida64.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("ida.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("Vmtoolsd.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("Vmwaretrat.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("Vmwareuser.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("Vmacthlp.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("vboxservice.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("vboxtray.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("KsDumper.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("ReClass.NET.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("x64dbg.exe") != 0)
		{
			bsod();
		}
		else if (FindProcessId2("OLLYDBG.exe") != 0)
		{
			bsod();
		}
	}

	void ScanBlacklistedWindows()
	{

		if (FindWindowA(NULL, xorstr_("The Wireshark Network Analyzer")))
		{
			bsod();
		}

		if (FindWindowA(NULL, xorstr_("Progress Telerik Fiddler Web Debugger")))
		{
			bsod();
		}

		if (FindWindowA(NULL, xorstr_("x64dbg")))
		{
			bsod();
		}

		if (FindWindowA(NULL, xorstr_("KsDumper")))
		{
			bsod();
		}
	}
	void KillDebuggers()
	{

		system("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1");
		system("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1");
		system("sc stop HTTPDebuggerPro >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq fiddler*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq wireshark*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq rawshark*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq charles*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq ida*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1");
		system("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1");
		system("sc stop HTTPDebuggerPro >nul 2>&1");
		system("sc stop KProcessHacker3 >nul 2>&1");
		system("sc stop KProcessHacker2 >nul 2>&1");
		system("sc stop KProcessHacker1 >nul 2>&1");
		system("sc stop wireshark >nul 2>&1");
		system("sc stop npf >nul 2>&1");
	}

	void AntiDebug() // we will create a thread and detach it for this to keep checking for these things
	{
		while (true)
		{
			DebuggerPresent();
			ScanBlacklistedWindows();
			ScanProccessListForBlacklistedProcess();
			KillDebuggers();
		}

	}

}