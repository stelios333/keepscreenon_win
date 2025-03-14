# Keep screen on
An extremely minimal and lightweight Windows tray application that prevents your screen from turning off.

## Features
- Runs in the system tray
- Toggle "Keep Screen On" via right-click menu

## Usage
1. Run `screenkeeper.exe`
2. Look for the tray icon in the system tray (bottom right)
3. Right-click the icon to access the menu
4. Toggle "Keep Screen On" (checked = enabled)
5. Select "Exit" to close the application

When enabled, your screen will stay on regardless of power settings. When disabled or exiting, normal power management resumes.

### Building
From Linux for 64-bit Windows:
```bash
x86_64-w64-mingw32-g++ -o screenkeeper.exe trayapp.cpp -static-libgcc -static-libstdc++ -luser32 -lshell32 -mwindows
```
For other OSes you'll have to figure it out yourself.