#include "c_utils.h"

bool c_utils::open_wp_key( const HKEY hkey, const char* sub_key ) {
	if ( RegOpenKeyEx( hkey, sub_key, 0,
					   KEY_ALL_ACCESS, &this->m_key ) ) {
		return false;
	}

	return true;
}

bool c_utils::change_key( ) {
	if ( !this->open_wp_key( HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\ActiveDesktop" ) )
		return false;

	uint32_t payload = 0;
	if ( RegSetValueEx( this->m_key, "NoChangingWallPaper", 0, REG_DWORD, reinterpret_cast<LPBYTE>(&payload),
						sizeof payload ) ) {
		return false;
	}

	RegCloseKey( this->m_key );
	return true;
}

bool c_utils::set_image_value( const LPCWSTR sub_key, const bool close_key ) const {

	WCHAR path[80] = L"C:\\img.jpg";
	if ( RegSetValueExW( this->m_key, sub_key, 0, REG_SZ, reinterpret_cast<LPBYTE>(path),
						 sizeof( path ) ) ) {
		return false;
	}

	if ( close_key )
		RegCloseKey( this->m_key );

	return true;
}

bool c_utils::set_int_value( const char* sub_key, std::uint32_t payload, const bool close_key ) const {
	if ( RegSetValueEx( m_key, sub_key, 0, REG_DWORD, reinterpret_cast<LPBYTE>(&payload),
						sizeof( payload ) ) ) {
		return false;
	}

	if ( close_key )
		RegCloseKey( this->m_key );

	return true;
}

bool c_utils::create_key( const char* sub_key ) {
	if ( RegCreateKeyEx( this->m_key, sub_key, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
						 nullptr, &this->m_new_key, nullptr ) ) {
		return false;
	}

	this->m_key = this->m_new_key;
	return true;
}

void c_utils::init( ) {
	if ( cfg::m_force_update ) {
		if ( !this->open_wp_key( HKEY_CURRENT_USER, "Control Panel\\Desktop" ) )
			return;

		this->set_image_value( L"WallPaper" );

		if ( !this->open_wp_key( HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\" ) )
			return;

		this->create_key( "System" );
		if ( this->set_image_value( L"Wallpaper", false ) ) {
			// update window
			system( "rundll32.exe user32.dll, UpdatePerUserSystemParameters" );
		}

		/*
		 0 - in the center;
		 1 - pave;
		 2 - stretch;
		 3 - by size;
		 4 - filling;
		 5 - extension.
		*/
		this->set_int_value( "WallpaperStyle", 0, false );

		// fix issue with some access 
		RegDeleteKey( this->m_key, "" );
		RegCloseKey( this->m_key ); // lOl

		cfg::m_force_update = false;
	}

	if ( cfg::m_change_themes ) {
		if ( !this->open_wp_key( HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize" ) )
			return;

		const auto choosed_windows_theme = cfg::m_windows_dark_mode ? 0 : cfg::m_windows_light_mode ? 1 : 0;
		this->set_int_value( "SystemUsesLightTheme", choosed_windows_theme, false );

		const auto choosed_apps_theme = cfg::m_apps_dark_mode ? 0 : cfg::m_apps_light_mode ? 1 : 0;
		this->set_int_value( "AppsUseLightTheme", choosed_apps_theme, false );

		this->set_int_value( "EnableTransparency", cfg::m_enable_transparency, false );
		this->set_int_value( "ColorPrevalence", cfg::m_color_prevalence );
	}
}