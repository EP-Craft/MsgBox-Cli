# MessageBox CLI Tool

一个轻量级的Windows命令行消息框工具，通过DLL动态加载实现灵活的消息提示功能。

## 📋 功能特性

- 🚀 **轻量高效**：纯C语言编写，无额外依赖
- 🔧 **灵活调用**：支持5种消息框类型（普通、信息、警告、错误、询问）
- 🛡️ **安全可靠**：完善的参数验证和错误处理
- 📦 **模块化设计**：主程序与DLL分离，便于维护和扩展
- ⚡ **静默模式**：参数错误时静默退出，不干扰其他程序

## 📁 项目结构

```
MessageBox-CLI/
├── Main.exe          # 已编译的主程序
├── MsgBox.dll        # 已编译的消息框DLL
├── Main.c            # 主程序源代码
├── MsgBox.c          # DLL源代码
├── LICENSE           # MIT许可证
└── README.md         # 本文档
```

## 🚀 快速开始

### 方法一：使用预编译程序（推荐）

1. 下载仓库中的 `Main.exe` 和 `MsgBox.dll`
2. 将两个文件放在同一目录下
3. 打开命令提示符（CMD）或PowerShell
4. 运行以下命令：

```bash
Main.exe -type=1 -title="提示" -text="操作成功完成！"
```

### 方法二：从源代码编译

#### 编译DLL：
```bash
gcc -shared -o MsgBox.dll MsgBox.c -lkernel32 -luser32
```

#### 编译主程序：
```bash
gcc -o Main.exe Main.c -lkernel32 -luser32
```

## 📖 详细用法

### 基本语法
```bash
Main.exe -type=<类型> -title="标题" -text="消息内容"
```

### 参数说明

| 参数 | 必需 | 说明 | 示例 |
|------|------|------|------|
| `-type=` | ✅ | 消息框类型（0-4） | `-type=1` |
| `-title=` | ✅ | 消息框标题 | `-title="系统提示"` |
| `-text=` | ✅ | 消息内容 | `-text="文件保存成功"` |

### 消息框类型（type值）

| 值 | 类型 | 图标 | 适用场景 |
|----|------|------|----------|
| 0 | 普通 | 无图标 | 普通通知 |
| 1 | 信息 | ℹ️ | 信息提示 |
| 2 | 询问 | ❓ | 用户确认 |
| 3 | 警告 | ⚠️ | 警告信息 |
| 4 | 错误 | ❌ | 错误提示 |

### 使用示例

#### 1. 显示信息提示
```bash
Main.exe -type=1 -title="完成" -text="文件已成功保存！"
```

#### 2. 显示警告信息
```bash
Main.exe -type=3 -title="警告" -text="磁盘空间不足，请及时清理！"
```

#### 3. 显示错误提示
```bash
Main.exe -type=4 -title="错误" -text="无法连接到服务器，请检查网络连接。"
```

#### 4. 显示询问对话框
```bash
Main.exe -type=2 -title="确认" -text="确定要删除此文件吗？"
```

#### 5. 普通通知（无图标）
```bash
Main.exe -type=0 -title="通知" -text="程序将在5分钟后关闭"
```

## 🔧 技术特点

### 参数验证
- 检查所有必需参数是否存在
- 验证`type`值范围（0-4）
- 检查参数值是否为空
- 参数错误时静默退出（返回0）

### 安全特性
- 缓冲区溢出防护
- 空指针安全检查
- 手动字符串处理（避免C库依赖）
- 大小写不敏感的参数识别

### 错误处理
```c
// 参数无效时的处理流程
if (!CheckParametersValid(argc, argv)) {
    return 0; // 静默退出，不显示任何错误信息
}
```

## 💻 集成到其他程序

### 在批处理脚本中使用
```batch
@echo off
REM 显示完成提示
Main.exe -type=1 -title="批处理完成" -text="所有任务已执行完毕！"
pause
```

### 在Python中调用
```python
import subprocess
import os

def show_message(title, text, msg_type=1):
    """显示Windows消息框"""
    exe_path = os.path.join(os.path.dirname(__file__), "Main.exe")
    cmd = [exe_path, f"-type={msg_type}", f"-title={title}", f"-text={text}"]
    subprocess.run(cmd, check=False)

# 使用示例
show_message("Python脚本", "数据处理完成！", 1)
```

### 在AutoHotkey中调用
```autohotkey
; 显示消息框
Run, Main.exe -type=3 -title="AHK提示" -text="热键已激活"
```

## 🛠️ 开发指南

### 编译选项
```bash
# 调试版本（带调试信息）
gcc -g -o Main_debug.exe Main.c -lkernel32 -luser32

# 发布版本（优化大小）
gcc -Os -o Main.exe Main.c -lkernel32 -luser32

# DLL编译
gcc -shared -s -o MsgBox.dll MsgBox.c -lkernel32 -luser32
```

### 扩展DLL功能
要添加新的消息框类型，修改`MsgBox.c`中的`ShowMsgBox`函数：

```c
// 添加新的图标类型
case 5: icon = MB_ICONASTERISK; break;
```

### 自定义编译
如果需要修改图标或添加版本信息，可以创建资源文件（.rc）并链接：

```bash
windres resources.rc -o resources.o
gcc -o Main.exe Main.c resources.o -lkernel32 -luser32
```

## 📊 参数验证规则

程序会严格检查以下条件：
1. ✅ 三个参数（-type, -title, -text）必须全部提供
2. ✅ 每个参数必须有值（不能是 `-type=` 这样的空值）
3. ✅ type值必须是0-4之间的整数
4. ✅ 参数顺序无关紧要
5. ✅ 参数大小写不敏感（-TYPE, -Title, -TEXT都可以）

## ⚠️ 注意事项

1. **DLL依赖**：`Main.exe` 必须与 `MsgBox.dll` 在同一目录
2. **Windows专用**：仅适用于Windows操作系统
3. **静默退出**：参数错误时程序无任何输出，直接退出
4. **编码问题**：目前仅支持ANSI字符，中文可能需要系统语言支持

## 🔍 故障排除

| 问题 | 可能原因 | 解决方案 |
|------|----------|----------|
| "程序无法启动" | 缺少DLL | 确保MsgBox.dll与Main.exe在同一目录 |
| 无任何反应 | 参数错误 | 检查参数格式和值是否正确 |
| 乱码显示 | 编码问题 | 使用英文或确保系统支持中文字符集 |
| 无法编译 | 缺少编译器 | 安装MinGW或Visual Studio编译工具 |

## 📄 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件。

## 🤝 贡献指南

欢迎提交Issue和Pull Request！在贡献代码时请注意：

1. 保持代码风格一致
2. 添加适当的注释
3. 更新相关文档
4. 测试所有更改

## 📞 支持

如果你遇到问题或有建议：
1. 查看本文档的"故障排除"部分
2. 在GitHub仓库提交Issue
3. 确保提供详细的错误信息和复现步骤

---

**提示**：对于生产环境，建议将程序添加到系统PATH或创建快捷方式以便快速访问。
