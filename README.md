# Windows Changer ![Platform](https://img.shields.io/badge/platform-windows-blue?style=flat) ![LANG](https://img.shields.io/badge/language-C%2B%2B-brightgreen?style=flat ) 
Made for developers who need this code, not for normal Windows users.
# Features
- Windows wallpaper changer 
- Enable Windows light theme
- Enable Windows dark theme
- Enable light apps colors
- Enable dark apps colors
- Enable transparency
- Enable color prevalence
# How to use?
- Сlick on the button of the desired function and all changes will take effect immediately!
# How does wallpaper changer work?
- Move your image along this path: **"C:\"** and be sure to name the file **"img"** and you need it to have a **jpg format** (all this can be changed in the source)
- Click on the big "Force update" button and you're done!
# Use case (wallpaper changer)
```cpp
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
	}
```
# Preview
![App menu](https://i.imgur.com/H2IUb4k.png)
