#include "utils/c_utils.h"
#include "setup/c_setup.h"
#include "ui/c_ui.h"

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow ) {
	WNDCLASSEX wc = { sizeof( WNDCLASSEX ), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle( NULL ), NULL, NULL, NULL, NULL, "Windows Changer", NULL };
	RegisterClassEx( &wc );
	g_ctx->m_main_hwnd = CreateWindow( wc.lpszClassName, "Windows Changer", WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL );

	if ( !g_ctx->create_device_d3d( g_ctx->m_main_hwnd ) ) {
		g_ctx->cleanup_device_d3d( );
		UnregisterClass( wc.lpszClassName, wc.hInstance );
		return 1;
	}

	ShowWindow( g_ctx->m_main_hwnd, SW_HIDE );
	UpdateWindow( g_ctx->m_main_hwnd );

	ImGui::CreateContext( );

	ImGuiIO& io = ImGui::GetIO( );
	io.IniFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle( );
	if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init( g_ctx->m_main_hwnd );
	ImGui_ImplDX9_Init( g_ctx->m_pd3d_device );

	ImGui::StyleColorsDark( );

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while ( msg.message != WM_QUIT ) {
		if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
			continue;
		}

		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );
		{
			g_ui->render( );
		}
		ImGui::EndFrame( );

		g_utils->init( );

		g_ctx->m_pd3d_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0 );
		if ( g_ctx->m_pd3d_device->BeginScene( ) >= 0 ) {
			ImGui::Render( );
			ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
			g_ctx->m_pd3d_device->EndScene( );
		}

		if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
			ImGui::UpdatePlatformWindows( );
			ImGui::RenderPlatformWindowsDefault( );
		}

		const auto result = g_ctx->m_pd3d_device->Present( NULL, NULL, NULL, NULL );

		if ( result == D3DERR_DEVICELOST && g_ctx->m_pd3d_device->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET ) {
			g_ctx->reset_device( );
		}
	}

	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );

	g_ctx->cleanup_device_d3d( );
	DestroyWindow( g_ctx->m_main_hwnd );
	UnregisterClass( wc.lpszClassName, wc.hInstance );

	return 0;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	if ( ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam ) )
		return true;

	switch ( msg ) {
		case WM_SIZE:
			if ( g_ctx->m_pd3d_device != NULL && wParam != SIZE_MINIMIZED ) {
				g_ctx->m_d3dpp.BackBufferWidth = LOWORD( lParam );
				g_ctx->m_d3dpp.BackBufferHeight = HIWORD( lParam );
				g_ctx->reset_device( );
			}
			return 0;
		case WM_SYSCOMMAND:
			if ( (wParam & 0xfff0) == SC_KEYMENU )
				return 0;
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}