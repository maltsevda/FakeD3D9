#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "FakeDirect3D9.h"

struct OriginalLibrary
{
	HMODULE hDll;
	FARPROC D3DPERF_BeginEvent;
	FARPROC D3DPERF_EndEvent;
	FARPROC D3DPERF_GetStatus;
	FARPROC D3DPERF_QueryRepeatFrame;
	FARPROC D3DPERF_SetMarker;
	FARPROC D3DPERF_SetOptions;
	FARPROC D3DPERF_SetRegion;
	FARPROC DebugSetLevel;
	FARPROC DebugSetMute;
	FARPROC Direct3D9EnableMaximizedWindowedModeShim;
	FARPROC Direct3DCreate9;
	FARPROC Direct3DCreate9Ex;
	FARPROC Direct3DShaderValidatorCreate9;
	FARPROC PSGPError;
	FARPROC PSGPSampleTexture;
} d3d9dll;

extern "C" __declspec(naked) void Fake_D3DPERF_BeginEvent()			{ _asm { jmp[d3d9dll.D3DPERF_BeginEvent] } }
extern "C" __declspec(naked) void Fake_D3DPERF_EndEvent()			{ _asm { jmp[d3d9dll.D3DPERF_EndEvent] } }
extern "C" __declspec(naked) void Fake_D3DPERF_GetStatus()			{ _asm { jmp[d3d9dll.D3DPERF_GetStatus] } }
extern "C" __declspec(naked) void Fake_D3DPERF_QueryRepeatFrame()	{ _asm { jmp[d3d9dll.D3DPERF_QueryRepeatFrame] } }
extern "C" __declspec(naked) void Fake_D3DPERF_SetMarker()			{ _asm { jmp[d3d9dll.D3DPERF_SetMarker] } }
extern "C" __declspec(naked) void Fake_D3DPERF_SetOptions()			{ _asm { jmp[d3d9dll.D3DPERF_SetOptions] } }
extern "C" __declspec(naked) void Fake_D3DPERF_SetRegion()			{ _asm { jmp[d3d9dll.D3DPERF_SetRegion] } }
extern "C" __declspec(naked) void Fake_DebugSetLevel()				{ _asm { jmp[d3d9dll.DebugSetLevel] } }
extern "C" __declspec(naked) void Fake_DebugSetMute()				{ _asm { jmp[d3d9dll.DebugSetMute] } }
extern "C" __declspec(naked) void Fake_Direct3D9EnableMaximizedWindowedModeShim() { _asm { jmp[d3d9dll.Direct3D9EnableMaximizedWindowedModeShim] } }
// extern "C" __declspec(naked) void Fake_Direct3DCreate9()			{ _asm { jmp[d3d9dll.Direct3DCreate9] } }
extern "C" __declspec(naked) void Fake_Direct3DCreate9Ex()			{ _asm { jmp[d3d9dll.Direct3DCreate9Ex] } }
extern "C" __declspec(naked) void Fake_Direct3DShaderValidatorCreate9() { _asm { jmp[d3d9dll.Direct3DShaderValidatorCreate9] } }
extern "C" __declspec(naked) void Fake_PSGPError()					{ _asm { jmp[d3d9dll.PSGPError] } }
extern "C" __declspec(naked) void Fake_PSGPSampleTexture()			{ _asm { jmp[d3d9dll.PSGPSampleTexture] } }

extern "C" IDirect3D9* WINAPI Fake_Direct3DCreate9(UINT SDKVersion)
{
	typedef IDirect3D9* (WINAPI * DIRECT3DCREATEPROC)(UINT SDKVersion);
	DIRECT3DCREATEPROC Direct3DCreate9Proc = (DIRECT3DCREATEPROC)d3d9dll.Direct3DCreate9;
	IDirect3D9* pFakeDirect3D9 = Direct3DCreate9Proc(SDKVersion);
	return new FakeDirect3D9(pFakeDirect3D9);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		WCHAR path[MAX_PATH];
		UINT length = GetSystemDirectoryW(path, MAX_PATH - 10);
		CopyMemory(path + length, L"\\d3d9.dll", sizeof(WCHAR) * 11);
		d3d9dll.hDll = LoadLibraryW(path);
		if (!d3d9dll.hDll)
		{
			MessageBoxW(0, L"Cannot load original d3d9.dll library", L"d3d9.dll proxy", MB_ICONERROR);
			ExitProcess(0);
		}
		d3d9dll.D3DPERF_BeginEvent = GetProcAddress(d3d9dll.hDll, "D3DPERF_BeginEvent");
		d3d9dll.D3DPERF_EndEvent = GetProcAddress(d3d9dll.hDll, "D3DPERF_EndEvent");
		d3d9dll.D3DPERF_GetStatus = GetProcAddress(d3d9dll.hDll, "D3DPERF_GetStatus");
		d3d9dll.D3DPERF_QueryRepeatFrame = GetProcAddress(d3d9dll.hDll, "D3DPERF_QueryRepeatFrame");
		d3d9dll.D3DPERF_SetMarker = GetProcAddress(d3d9dll.hDll, "D3DPERF_SetMarker");
		d3d9dll.D3DPERF_SetOptions = GetProcAddress(d3d9dll.hDll, "D3DPERF_SetOptions");
		d3d9dll.D3DPERF_SetRegion = GetProcAddress(d3d9dll.hDll, "D3DPERF_SetRegion");
		d3d9dll.DebugSetLevel = GetProcAddress(d3d9dll.hDll, "DebugSetLevel");
		d3d9dll.DebugSetMute = GetProcAddress(d3d9dll.hDll, "DebugSetMute");
		d3d9dll.Direct3D9EnableMaximizedWindowedModeShim = GetProcAddress(d3d9dll.hDll, "Direct3D9EnableMaximizedWindowedModeShim");
		d3d9dll.Direct3DCreate9 = GetProcAddress(d3d9dll.hDll, "Direct3DCreate9");
		d3d9dll.Direct3DCreate9Ex = GetProcAddress(d3d9dll.hDll, "Direct3DCreate9Ex");
		d3d9dll.Direct3DShaderValidatorCreate9 = GetProcAddress(d3d9dll.hDll, "Direct3DShaderValidatorCreate9");
		d3d9dll.PSGPError = GetProcAddress(d3d9dll.hDll, "PSGPError");
		d3d9dll.PSGPSampleTexture = GetProcAddress(d3d9dll.hDll, "PSGPSampleTexture");
		break;
	}
	case DLL_PROCESS_DETACH:
		FreeLibrary(d3d9dll.hDll);
		break;
	}
	return TRUE;
}
