#include <windows.h>

// DLL入口点（可选，但推荐包含）
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    return TRUE;  // 总是返回TRUE
}

// 消息框显示函数
__declspec(dllexport) void __stdcall ShowMsgBox(int type, char* title, char* text) {
    // 定义图标类型
    UINT icon = 0;
    
    // 安全处理空指针
    char safeTitle[256] = "";
    char safeText[1024] = "";
    
    // 复制参数到安全缓冲区
    if (title) {
        int i = 0;
        while (i < sizeof(safeTitle) - 1 && title[i]) {
            safeTitle[i] = title[i];
            i++;
        }
        safeTitle[i] = 0;
    }
    
    if (text) {
        int i = 0;
        while (i < sizeof(safeText) - 1 && text[i]) {
            safeText[i] = text[i];
            i++;
        }
        safeText[i] = 0;
    }
    
    // 根据type设置图标
    switch (type) {
        case 1: icon = MB_ICONINFORMATION; break;
        case 2: icon = MB_ICONQUESTION; break;
        case 3: icon = MB_ICONWARNING; break;
        case 4: icon = MB_ICONERROR; break;
        default: icon = 0; break;
    }
    
    // 显示消息框
    MessageBoxA(NULL, safeText, safeTitle, MB_OK | icon);
}

// 为兼容性添加另一个导出名称
__declspec(dllexport) void __stdcall ShowMessageBox(int type, char* title, char* text) {
    ShowMsgBox(type, title, text);
}