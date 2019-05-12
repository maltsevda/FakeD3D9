#pragma once

#include <d3d9.h>

class FakeDirect3D9 : public IDirect3D9
{
public:
	FakeDirect3D9(IDirect3D9 *pOriginal);
    virtual ~FakeDirect3D9(void);

    // The original DX9 function definitions
	virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj);
    virtual COM_DECLSPEC_NOTHROW ULONG    STDMETHODCALLTYPE AddRef(void);
	virtual COM_DECLSPEC_NOTHROW ULONG    STDMETHODCALLTYPE Release(void);
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE RegisterSoftwareDevice(void* pInitializeFunction);
	virtual COM_DECLSPEC_NOTHROW UINT     STDMETHODCALLTYPE GetAdapterCount(void);
	virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) ;
    virtual COM_DECLSPEC_NOTHROW UINT     STDMETHODCALLTYPE GetAdapterModeCount(UINT Adapter, D3DFORMAT Format);
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) ;
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode) ;
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) ;
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) ;
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) ;
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) ;
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat);
    virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) ;
	virtual COM_DECLSPEC_NOTHROW HMONITOR STDMETHODCALLTYPE GetAdapterMonitor(UINT Adapter) ;
	virtual COM_DECLSPEC_NOTHROW HRESULT  STDMETHODCALLTYPE CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) ;
    // The original DX9 function definitions

private:
   	IDirect3D9 *m_pIDirect3D9;
};
