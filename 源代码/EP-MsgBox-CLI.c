#include <windows.h>

// 自定义字符串转换函数 - 不使用C库
void StringToLower(const char* src, char* dest, int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && src[i]) {
        char c = src[i];
        // 手动转换大小写（A-Z转a-z）
        dest[i] = (c >= 'A' && c <= 'Z') ? (c + 32) : c;
        i++;
    }
    dest[i] = 0;
}

// 检查字符串是否以指定前缀开头（不区分大小写）
int StartsWithNoCase(const char* str, const char* prefix) {
    while (*prefix) {
        char c1 = *str;
        char c2 = *prefix;
        
        // 手动转换并比较字符
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        
        if (c1 != c2) return 0;
        str++;
        prefix++;
    }
    return 1;
}

// 解析整数（简单实现，避免使用atoi）
int ParseInt(const char* str) {
    int result = 0;
    int sign = 1;
    
    if (*str == '-') {
        sign = -1;
        str++;
    }
    
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return result * sign;
}

// 复制字符串（安全版本）
void SafeCopy(char* dest, const char* src, int maxLen) {
    int i = 0;
    while (i < maxLen - 1 && src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
}

// 检查参数值是否为空
int IsValueEmpty(const char* arg) {
    // 找到等号位置
    const char* eqPos = arg;
    while (*eqPos && *eqPos != '=') eqPos++;
    
    // 如果没有等号或等号后面没有字符，则值为空
    if (*eqPos != '=') return 1;  // 没有等号，格式错误
    
    eqPos++; // 跳过等号
    
    // 检查等号后面的内容是否为空
    return (*eqPos == 0);
}

// 获取参数值（跳过参数名和等号）
const char* GetValuePart(const char* arg) {
    const char* pos = arg;
    while (*pos && *pos != '=') pos++;
    if (*pos == '=') pos++;
    return pos;
}

// 检查参数是否有效（包括type值范围和空值检查）
int CheckParametersValid(int argc, char* argv[]) {
    int hasType = 0, hasTitle = 0, hasText = 0;
    int typeValue = 0;
    char lowerArg[1024];
    
    // 第一遍：检查参数是否存在并验证type值
    for (int i = 1; i < argc; i++) {
        StringToLower(argv[i], lowerArg, sizeof(lowerArg));
        
        if (StartsWithNoCase(lowerArg, "-type=")) {
            // 检查参数值是否为空
            if (IsValueEmpty(argv[i])) {
                return 0; // 值为空，静默退出
            }
            
            hasType = 1;
            
            // 解析type值并检查是否在0-4范围内
            const char* value = GetValuePart(argv[i]);
            
            typeValue = ParseInt(value);
            
            // 如果type值大于4或小于0，参数无效
            if (typeValue < 0 || typeValue > 4) {
                return 0; // type值无效，静默退出
            }
        } 
        else if (StartsWithNoCase(lowerArg, "-title=")) {
            // 检查参数值是否为空
            if (IsValueEmpty(argv[i])) {
                return 0; // 值为空，静默退出
            }
            
            hasTitle = 1;
        }
        else if (StartsWithNoCase(lowerArg, "-text=")) {
            // 检查参数值是否为空
            if (IsValueEmpty(argv[i])) {
                return 0; // 值为空，静默退出
            }
            
            hasText = 1;
        }
    }
    
    // 检查是否三个参数都存在且都有非空值
    return (hasType && hasTitle && hasText);
}

int main(int argc, char* argv[]) {
    // 检查参数是否全部提供且有效
    if (!CheckParametersValid(argc, argv)) {
        return 0; // 静默退出
    }
    
    // 重新解析参数
    int type = 0;
    char title[256] = {0};
    char text[1024] = {0};
    
    for (int i = 1; i < argc; i++) {
        if (StartsWithNoCase(argv[i], "-type=")) {
            // 获取值部分
            const char* value = GetValuePart(argv[i]);
            
            type = ParseInt(value);
            // 由于CheckParametersValid已经验证过，这里type值一定在0-4范围内
        }
        else if (StartsWithNoCase(argv[i], "-title=")) {
            const char* value = GetValuePart(argv[i]);
            
            SafeCopy(title, value, sizeof(title));
        }
        else if (StartsWithNoCase(argv[i], "-text=")) {
            const char* value = GetValuePart(argv[i]);
            
            SafeCopy(text, value, sizeof(text));
        }
    }
    
    // 加载DLL并调用 - 改为EP-MsgBox.dll
    HMODULE dll = LoadLibraryA("EP-MsgBox.dll");
    if (dll) {
        // 获取函数指针
        void (__stdcall *ShowMsgBox)(int, char*, char*) = 
            (void (__stdcall *)(int, char*, char*))GetProcAddress(dll, "ShowMsgBox");
        
        if (ShowMsgBox) {
            ShowMsgBox(type, title, text);
        }
        
        FreeLibrary(dll);
    }
    
    return 0;
}
