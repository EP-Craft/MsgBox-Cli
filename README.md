# MessageBox CLI Tool

一个轻量级的Windows命令行消息框工具，无需安装，开箱即用。

## 📦 快速开始

### 第一步：下载文件
1. 进入 `.\可执行程序` 目录
2. 下载以下两个文件到同一文件夹：
   - `Main.exe` - 主程序
   - `MsgBox.dll` - 必需的动态链接库

### 第二步：基本使用
打开命令提示符（CMD）或PowerShell，运行：

```bash
Main.exe -type=1 -title="提示" -text="操作成功！"
```

## 🚀 完整使用方法

### 基本语法
```bash
Main.exe -type=<类型> -title="标题" -text="消息内容"
```

### 必需参数

| 参数 | 说明 | 示例 |
|------|------|------|
| `-type=` | 消息框类型（0-4） | `-type=1` |
| `-title=` | 窗口标题 | `-title="系统通知"` |
| `-text=` | 显示的消息内容 | `-text="文件已保存"` |

### 消息框类型对照表

| 值 | 图标 | 用途 |
|----|------|------|
| 0 | 无图标 | 普通通知 |
| 1 | ℹ️ 信息 | 成功提示、信息展示 |
| 2 | ❓ 问号 | 确认对话框 |
| 3 | ⚠️ 警告 | 警告信息 |
| 4 | ❌ 错误 | 错误提示 |

## 📝 实用示例

### 1. 显示成功提示
```bash
Main.exe -type=1 -title="操作完成" -text="文件已成功上传到服务器。"
```

### 2. 显示警告信息
```bash
Main.exe -type=3 -title="磁盘警告" -text="C盘剩余空间不足10%，请及时清理。"
```

### 3. 显示错误提示
```bash
Main.exe -type=4 -title="连接失败" -text="无法连接到数据库，请检查网络设置。"
```

### 4. 显示确认对话框
```bash
Main.exe -type=2 -title="删除确认" -text="确定要永久删除此文件吗？"
```

### 5. 简单通知（无图标）
```bash
Main.exe -type=0 -title="提醒" -text="会议将在15分钟后开始。"
```

## 🔧 集成到脚本中

### 在批处理脚本中使用
```batch
@echo off
echo 正在处理文件...
REM 显示完成提示
Main.exe -type=1 -title="批处理完成" -text="所有文件处理完毕！"
pause
```

### 在Python脚本中调用
```python
import subprocess
import os

def show_msg(title, message, msg_type=1):
    """显示Windows消息框"""
    exe_path = r".\可执行程序\Main.exe"  # 根据实际路径调整
    cmd = [exe_path, f"-type={msg_type}", f"-title={title}", f"-text={message}"]
    subprocess.run(cmd)

# 使用示例
show_msg("Python脚本", "数据处理完成！")
```

### 在AutoHotkey脚本中使用
```autohotkey
; 显示热键激活提示
Run, Main.exe -type=1 -title="AHK提示" -text="Ctrl+Alt+S 热键已启用"
```

## ⚠️ 重要注意事项

1. **文件依赖**：必须确保 `Main.exe` 和 `MsgBox.dll` 在同一目录下
2. **静默退出**：如果参数错误或缺失，程序会静默退出（无错误提示）
3. **参数规则**：
   - 三个参数必须全部提供
   - 参数值不能为空（如 `-title=` 是无效的）
   - type值必须是0-4的整数
   - 参数顺序任意，大小写不敏感

## 🔍 常见问题

### Q: 运行程序没反应？
**A:** 检查：
1. `MsgBox.dll` 是否在同一目录
2. 参数格式是否正确
3. 是否提供了全部三个参数

### Q: 如何验证程序是否正常工作？
**A:** 运行测试命令：
```bash
Main.exe -type=1 -title="测试" -text="程序运行正常"
```

### Q: 可以自定义图标吗？
**A:** 当前版本支持5种预设图标（0-4），如需更多类型需要修改源代码后重新编译。

### Q: 支持中文字符吗？
**A:** 支持，但请确保系统语言设置正确。

## 📁 文件说明

```
.\可执行程序\
├── Main.exe      # 主程序文件
└── MsgBox.dll    # 消息框功能库（必需）
```

## 📄 许可证

MIT License - 详见项目根目录的LICENSE文件。

---

**提示**：如需查看或修改源代码，请访问 `.\源代码` 目录。
