#include "FakeDirect3D9.h"
#include "FakeDirect3DDevice9.h"

FakeDirect3D9::FakeDirect3D9(IDirect3D9 *pOriginal) :
	m_pIDirect3D9(pOriginal)
{
}

FakeDirect3D9::~FakeDirect3D9(void)
{
}

HRESULT FakeDirect3D9::QueryInterface(REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;
	HRESULT hRes = m_pIDirect3D9->QueryInterface(riid, ppvObj);
	if (SUCCEEDED(hRes))
		*ppvObj = this;
	return hRes;
}

ULONG FakeDirect3D9::AddRef(void)
{
	return(m_pIDirect3D9->AddRef());
}

ULONG FakeDirect3D9::Release(void)
{
	ULONG count = m_pIDirect3D9->Release();
	if (count < 1)
		delete(this);
	return(count);
}

HRESULT FakeDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return(m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction));
}

UINT FakeDirect3D9::GetAdapterCount(void)
{
	return(m_pIDirect3D9->GetAdapterCount());
}

HRESULT FakeDirect3D9::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return(m_pIDirect3D9->GetAdapterIdentifier(Adapter,Flags,pIdentifier));
}

UINT FakeDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return(m_pIDirect3D9->GetAdapterModeCount(Adapter, Format));
}

HRESULT FakeDirect3D9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
	return(m_pIDirect3D9->EnumAdapterModes(Adapter,Format,Mode,pMode));
}

HRESULT FakeDirect3D9::GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode)
{
	return(m_pIDirect3D9->GetAdapterDisplayMode(Adapter,pMode));
}

HRESULT FakeDirect3D9::CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed)
{
	return(m_pIDirect3D9->CheckDeviceType(iAdapter,DevType,DisplayFormat,BackBufferFormat,bWindowed));
}

HRESULT FakeDirect3D9::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
	return(m_pIDirect3D9->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat));
}

HRESULT FakeDirect3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
	return(m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels));
}

HRESULT FakeDirect3D9::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
	return(m_pIDirect3D9->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat));
}

HRESULT FakeDirect3D9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
	return(m_pIDirect3D9->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat));
}

HRESULT FakeDirect3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
{
	return(m_pIDirect3D9->GetDeviceCaps(Adapter,DeviceType,pCaps));
}

HMONITOR FakeDirect3D9::GetAdapterMonitor(UINT Adapter)
{
	return(m_pIDirect3D9->GetAdapterMonitor(Adapter));
}

HRESULT FakeDirect3D9::CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	if (pPresentationParameters->BackBufferWidth == 800 &&
		pPresentationParameters->BackBufferHeight == 600)
	{
		pPresentationParameters->BackBufferWidth = 1920;
		pPresentationParameters->BackBufferHeight = 1080;
	}
	pPresentationParameters->PresentationInterval = D3DPRESENT_INTERVAL_ONE; // force VSYNC
	HRESULT hres = m_pIDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	*ppReturnedDeviceInterface = new FakeDirect3DDevice9(*ppReturnedDeviceInterface);
	return(hres);
}
