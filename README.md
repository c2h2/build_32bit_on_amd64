# 在 AMD64 系统上构建 32 位程序

本项目演示如何在 AMD64 (x86_64) 系统上交叉编译 32 位程序。

## 编译器要求

### 在 AMD64 系统上安装 32 位交叉编译工具

**Ubuntu/Debian:**
```bash
# 添加 i386 架构支持
sudo dpkg --add-architecture i386

sudo apt update
sudo apt install gcc-multilib g++-multilib
```

**或者安装专用的 i686 交叉编译器:**
```bash
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install gcc-i686-linux-gnu g++-i686-linux-gnu
```

**Qt5 开发环境:**
```bash
# 安装 Qt5 开发包
sudo apt install qtbase5-dev qt5-qmake

# 安装 32 位 Qt5 运行时库（用于交叉编译）
sudo apt install libqt5widgets5:i386 libqt5core5t64:i386 libqt5gui5t64:i386
```

**CentOS/RHEL/Fedora:**
```bash
# Fedora
sudo dnf install glibc-devel.i686 libgcc.i686

# CentOS/RHEL
sudo yum install glibc-devel.i686 libgcc.i686
```

## 运行环境说明

### AMD64 架构兼容性

AMD64 (x86_64) 架构具有向后兼容性，可以同时运行：
- **64 位程序**: 原生支持，性能最佳
- **32 位 legacy 程序**: 通过兼容层运行，需要额外的 32 位库支持

### 为什么需要 32 位库？

64 位系统默认只安装 64 位版本的系统库（如 libc）。要运行 32 位程序，需要安装对应的 32 位库文件。这种设计允许：
1. **节省空间**: 默认不安装不常用的 32 位库
2. **按需安装**: 只在需要运行 32 位程序时才安装相关库
3. **双重支持**: 同一系统可同时运行 32 位和 64 位程序

**安装 32 位运行时库:**

**Ubuntu/Debian:**
```bash
sudo apt install libc6:i386 libgcc-s1:i386 libstdc++6:i386
```

**CentOS/RHEL/Fedora:**
```bash
# Fedora
sudo dnf install glibc.i686 libstdc++.i686

# CentOS/RHEL  
sudo yum install glibc.i686 libstdc++.i686
```

### 验证安装

检查程序架构和运行情况：
```bash
# 查看程序架构
file test_length_32bit test_length_64bit

# 运行 32 位程序（需要 32 位库支持）
./test_length_32bit

# 运行 64 位程序（原生支持）
./test_length_64bit
```

**预期输出:**
```
test_length_32bit: ELF 32-bit LSB executable, Intel 80386
test_length_64bit: ELF 64-bit LSB executable, x86-64
```

如果 32 位程序出现 "No such file or directory" 错误，说明缺少 32 位运行时库。

## 构建和运行

### C 语言演示

```bash
# 编译 32 位版本
./build_64bit_to_32bit.sh

# 编译 64 位版本  
./build_native.sh

# 运行测试
./test_length_32bit  # 应该输出: Long size: 4
./test_length_64bit  # 应该输出: Long size: 8
```

### C++ 语言演示

```bash
# 编译 32 位 C++ 版本
./build_cpp_32bit.sh

# 编译 64 位 C++ 版本
./build_cpp_native.sh

# 运行 C++ 测试
./demo_32bit  # 显示 32 位架构的数据类型大小
./demo_64bit  # 显示 64 位架构的数据类型大小
```

**C++ 演示程序特点:**
- 使用现代 C++ 特性（STL容器、智能指针、类）
- 显示不同架构下基本数据类型的大小差异
- 验证交叉编译的正确性

### Qt5 GUI 演示

```bash
# 编译 32 位 Qt5 版本
./build_qt_32bit.sh

# 编译 64 位 Qt5 版本
./build_qt_native.sh

# 运行 Qt5 GUI 程序
./qt_demo_32bit  # 32 位 Qt5 GUI 应用
./qt_demo_64bit  # 64 位 Qt5 GUI 应用
```

**Qt5 演示程序特点:**
- 完整的 GUI 应用程序，包含窗口、按钮、文本框等控件
- 实时显示当前架构信息和数据类型大小
- 演示交互式界面在不同架构下的兼容性
- 包含进度条、滑块等动态元素

### 一键构建所有演示

```bash
# 构建所有项目（C、C++、Qt5 的 32 位和 64 位版本）
./build_all.sh
```

这个脚本会自动构建所有演示程序并显示构建状态，方便一次性验证整个交叉编译环境。

## 常见问题

1. **编译错误**: 缺少交叉编译工具链
   - 解决: 安装 `gcc-multilib` 或 `gcc-i686-linux-gnu`

2. **运行错误**: "No such file or directory"
   - 解决: 安装 32 位运行时库 `libc6:i386`

3. **链接错误**: 找不到 32 位库文件
   - 解决: 确保安装了完整的 32 位开发库

4. **Qt5 编译错误**: 缺少 Qt5 开发包
   - 解决: `sudo apt install qtbase5-dev qt5-qmake`

5. **Qt5 32位编译失败**: 缺少 32 位 Qt5 库
   - 解决: `sudo apt install libqt5widgets5:i386 libqt5core5t64:i386 libqt5gui5t64:i386`

6. **Qt5 程序无法运行**: 缺少 GUI 环境
   - 解决: 确保有 X11 或 Wayland 显示环境，或使用 `export DISPLAY=:0`