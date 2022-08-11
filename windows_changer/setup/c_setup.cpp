#include "c_setup.h"

bool c_setup::create_device_d3d( HWND hWnd ) {
	if ( (m_pd3d = Direct3DCreate9( D3D_SDK_VERSION )) == NULL )
		return false;

	ZeroMemory( &m_d3dpp, sizeof( m_d3dpp ) );
	m_d3dpp.Windowed = TRUE;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	if ( m_pd3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_pd3d_device ) < 0 )
		return false;
	return true;
}

void c_setup::cleanup_device_d3d( ) {
	if ( m_pd3d_device ) { m_pd3d_device->Release( ); m_pd3d_device = NULL; }
	if ( m_pd3d ) { m_pd3d->Release( ); m_pd3d = NULL; }
}

void c_setup::reset_device( ) {
	ImGui_ImplDX9_InvalidateDeviceObjects( );
	HRESULT hr = m_pd3d_device->Reset( &m_d3dpp );
	if ( hr == D3DERR_INVALIDCALL )
		IM_ASSERT( 0 );
	ImGui_ImplDX9_CreateDeviceObjects( );
}