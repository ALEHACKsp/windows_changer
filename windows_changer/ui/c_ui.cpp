#include "c_ui.h"

void c_ui::render( ) {
	ImGui::SetNextWindowPos( m_window_pos, ImGuiCond_Once );
	ImGui::SetNextWindowSize( m_window_size );
	ImGui::SetNextWindowBgAlpha( 1.0f );

	static bool active = true;
	ImGui::Begin( "Loader", &active, m_window_flags );

	static std::uint32_t selected_tab = 0;

	{
		ImGui::BeginChild( "Tabs Panel", ImVec2{ 150.0f, 0.0f }, true );
		{
			ImGui::Spacing( );
			static constexpr const char* tabs[]{
				"Personalization",
			};

			for ( std::size_t i = 0; i < IM_ARRAYSIZE( tabs ); ++i ) {
				if ( ImGui::Selectable( tabs[i], selected_tab == i ) ) {
					selected_tab = i;
				}
			}
		}
		ImGui::EndChild( );
		ImGui::SameLine( );
	}

	{
		ImGui::BeginGroup( );
		{
			ImGui::Spacing( );
			switch ( selected_tab ) {
				case 0:
					this->draw_personalization_tab( ); break;
				default: break;
			}
		}
		ImGui::EndGroup( );
	}

	ImGui::End( );
}

void c_ui::init( ) {
	ImGui::StyleColorsDark( );
}

void c_ui::draw_personalization_tab( ) {
	ImGui::Checkbox( "Change windows themes", &cfg::m_change_themes );
	if ( cfg::m_change_themes ) {
		ImGui::Checkbox( "Enable Windows light theme", &cfg::m_windows_light_mode );
		ImGui::Checkbox( "Enable Windows dark theme", &cfg::m_windows_dark_mode );
		ImGui::Checkbox( "Enable light apps colors", &cfg::m_apps_light_mode );
		ImGui::Checkbox( "Enable dark apps colors", &cfg::m_apps_dark_mode );
		ImGui::Checkbox( "Enable transparency", &cfg::m_enable_transparency );
		ImGui::Checkbox( "Enable color prevalence", &cfg::m_color_prevalence );
	}
	ImGui::Button( "Force update", ImVec2( 100.0f, 29.0f ) ) ? cfg::m_force_update = true : cfg::m_force_update = false;
}