#pragma once

// windows
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <stdio.h>
#include <strsafe.h>

// dependencies
#include "ui/imgui/imgui.h"
#include "ui/imgui/imgui_impl_dx9.h"
#include "ui/imgui/imgui_impl_win32.h"

// graphics
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

namespace cfg {
	inline bool m_change_themes{};
	inline bool m_windows_dark_mode{};
	inline bool m_windows_light_mode{};

	inline bool m_apps_dark_mode{};
	inline bool m_apps_light_mode{};

	inline bool m_enable_transparency{};
	inline bool m_color_prevalence{};
	inline bool m_force_update{};
	inline bool m_force_update_2{};
	inline char m_dir_to_image{};
}