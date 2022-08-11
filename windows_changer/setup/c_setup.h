#pragma once
#include "../includes.h"

class c_setup {
public:
	HWND m_main_hwnd{};

	LPDIRECT3DDEVICE9        m_pd3d_device{};
	D3DPRESENT_PARAMETERS    m_d3dpp{};
	LPDIRECT3D9              m_pd3d{};

	void cleanup_device_d3d( );
	bool create_device_d3d( HWND hWnd );
	void reset_device( );
};

inline const auto g_ctx = std::make_unique<c_setup>( );