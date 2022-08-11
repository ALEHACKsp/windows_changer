#pragma once
#include "../includes.h"

class c_utils {
	HKEY m_key{}, m_new_key{};
public:
	bool create_key( const char* sub_key );
	bool open_wp_key( const HKEY hkey, const char* sub_key );
	void init( );
	bool change_key( );
	bool set_image_value( const LPCWSTR sub_key, const bool close_key = true ) const;
	bool set_int_value( const char* sub_key, std::uint32_t payload, const bool close_key = true ) const;
};

inline const auto g_utils = std::make_unique<c_utils>( );