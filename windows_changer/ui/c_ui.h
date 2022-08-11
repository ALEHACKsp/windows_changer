#pragma once
#include "../includes.h"

class c_ui {
	ImVec2 m_window_pos{ 700.0f, 200.0f }, m_window_size{ 700.0f, 500.0f };
	DWORD m_window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse;
public:
	void render( );
	void init( );
	void draw_personalization_tab( );
};

inline const auto g_ui = std::make_unique<c_ui>( );
