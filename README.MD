# Keep screen on
An extremely minimal and lightweight Windows tray application that prevents your screen from turning off.

## Features
- Runs in the system tray
- Toggle "Keep Screen On" via right-click menu
- Can be run automatically at startup

## Usage
1. Run `keepscreenon_x64.exe`
2. Choose whether you want the program to run on startup 
3. Look for the tray icon in the system tray (bottom right)
4. Right-click the icon to access the menu
5. Toggle "Keep Screen On" (checked = enabled)
6. Select "Exit" to close the application

When enabled, your screen will stay on regardless of power settings. When disabled or exiting, normal power management resumes.

### Compiling
From Linux for 64-bit Windows:
```bash
x86_64-w64-mingw32-g++ -o keepscreenon_x64.exe main.cpp -static -static-libgcc -static-libstdc++ -mwindows
```
For other OSes you'll have to figure it out yourself.