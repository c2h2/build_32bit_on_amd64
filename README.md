# 在 AMD64 系统上构建 32 位程序

本项目演示如何在 AMD64 (x86_64) 系统上**交叉编译** 32位 (i686) 程序，特别关注**2038年问题**的解决方案。

## 2038年问题背景

在传统32位Linux系统中，`time_t` 使用32位有符号整数存储Unix时间戳：
- **范围**: 1970年1月1日 至 2038年1月19日
- **问题**: 2038年1月19日后会发生整数溢出，导致时间回绕到1901年
- **影响**: 所有使用32位时间戳的程序和库都会受影响

### t64转换解决方案

Ubuntu 24.04引入了**t64包**（64位时间戳）来解决这个问题：
- **t64包**: 使用64位 `time_t`，支持到292,277,026,596年
- **兼容性**: 与32位程序完全兼容，ABI兼容
- **标识**: 包名包含"t64"后缀（如 `libqt5core5t64`）
- **强制性**: Ubuntu 24.04中已完全替换传统32位时间戳包

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

## 项目结构

```
.
├── src/                    # 源文件目录
│   ├── test_length.c      # C 语言演示程序
│   ├── demo.cpp           # C++ 演示程序
│   ├── qt_demo_simple.cpp # Qt5 GUI 演示程序
│   └── qt_demo_simple.pro # Qt5 项目文件
├── scripts/               # 构建脚本目录
│   ├── build_64bit_to_32bit.sh  # C 32位编译脚本
│   ├── build_native.sh          # C 64位编译脚本
│   ├── build_cpp_32bit.sh       # C++ 32位编译脚本
│   ├── build_cpp_native.sh      # C++ 64位编译脚本
│   ├── build_qt_32bit.sh        # Qt5 32位编译脚本
│   ├── build_qt_native.sh       # Qt5 64位编译脚本
│   └── build_all.sh             # 一键构建所有项目
├── build/                 # 构建输出目录（由构建脚本创建）
└── README.md             # 项目说明文档
```

## 构建和运行

### C 语言演示

```bash
# 编译 32 位版本
./scripts/build_64bit_to_32bit.sh

# 编译 64 位版本  
./scripts/build_native.sh

# 运行测试
./build/test_length_32bit  # 应该输出: Long size: 4
./build/test_length_64bit  # 应该输出: Long size: 8
```

### C++ 语言演示

```bash
# 编译 32 位 C++ 版本
./scripts/build_cpp_32bit.sh

# 编译 64 位 C++ 版本
./scripts/build_cpp_native.sh

# 运行 C++ 测试
./build/demo_32bit  # 显示 32 位架构的数据类型大小
./build/demo_64bit  # 显示 64 位架构的数据类型大小
```

**C++ 演示程序特点:**
- 使用现代 C++ 特性（STL容器、智能指针、类）
- 显示不同架构下基本数据类型的大小差异
- 验证交叉编译的正确性



## Qt5 开发环境:
```bash
# 安装 Qt5 开发包
sudo apt install qtbase5-dev qt5-qmake

# 安装 32 位 Qt5 运行时库（用于交叉编译）
sudo apt install libqt5widgets5:i386 libqt5core5t64:i386 libqt5gui5t64:i386
```

### Qt5 32位交叉编译解决方案

在Ubuntu 24.04中，Qt5库已全面转换为t64版本（64位时间戳支持），解决2038年时间溢出问题。本项目展示了在新系统上编译32位Qt5程序的两种方法：

#### 方案A：使用t64包（推荐）
**优点**: 官方支持，解决2038年问题，兼容性好
**缺点**: 包名包含"t64"后缀

```bash
# 安装32位t64版本Qt5库
sudo apt install libqt5widgets5t64:i386 libqt5core5t64:i386 libqt5gui5t64:i386

# 创建开发链接符号（本项目已自动处理）
sudo ln -sf /usr/lib/i386-linux-gnu/libQt5Core.so.5 /usr/lib/i386-linux-gnu/libQt5Core.so
sudo ln -sf /usr/lib/i386-linux-gnu/libQt5Gui.so.5 /usr/lib/i386-linux-gnu/libQt5Gui.so  
sudo ln -sf /usr/lib/i386-linux-gnu/libQt5Widgets.so.5 /usr/lib/i386-linux-gnu/libQt5Widgets.so
```

#### 方案B：使用传统兼容包（（旧 ABI，t32）
**优点**: 无t64后缀，与旧系统一致
**缺点**: Ubuntu 24.04中已不可用，存在2038年问题

做法是把 旧 32 位用户态 放进容器/chroot 里（如 Ubuntu 22.04 Jammy i386 或 Debian 12 Bookworm i386），在那里安装非 t64 的 Qt 包，再运行你的旧 32-bit 程序。不要在 24.04 宿主机上强行混装旧 ABI。

选项 B1：Jammy i386 chroot（Ubuntu 22.04）
```bash
sudo apt install debootstrap
sudo debootstrap --arch=i386 jammy /opt/jammy-i386 http://archive.ubuntu.com/ubuntu/
sudo chroot /opt/jammy-i386
apt update
apt install libqt5core5a libqt5gui5 libqt5widgets5  # 旧 ABI 套件
···


选项 B2：Jammy 的 libqt5core5a:i386 等仍为旧命名/旧 ABI。
```bash
选项 B2：Debian Bookworm i386 chroot
sudo apt install debootstrap
sudo debootstrap --arch=i386 bookworm /opt/bookworm-i386 http://deb.debian.org/debian
sudo chroot /opt/bookworm-i386
apt update
apt install libqt5core5a libqt5gui5 libqt5widgets5
···

**本项目采用方案一**，通过以下技术实现32位Qt5交叉编译：
1. 使用64位Qt5头文件（与32位兼容）
2. 链接32位t64版本Qt5库
3. 手动编译避开qmake配置复杂性
4. 自动创建必要的开发符号链接

### Qt5 GUI 演示

```bash
# 编译 32 位 Qt5 版本
./scripts/build_qt_32bit.sh

# 编译 64 位 Qt5 版本
./scripts/build_qt_native.sh

# 运行 Qt5 GUI 程序
./build/qt_demo_32bit  # 32 位 Qt5 GUI 应用
./build/qt_demo_64bit  # 64 位 Qt5 GUI 应用
```

**Qt5 演示程序特点:**
- 完整的 GUI 应用程序，包含窗口、按钮、文本框等控件
- 实时显示当前架构信息和数据类型大小
- 演示交互式界面在不同架构下的兼容性
- 包含进度条、滑块等动态元素

### 一键构建所有演示

```bash
# 构建所有项目（C、C++、Qt5 的 32 位和 64 位版本）
./scripts/build_all.sh
```

这个脚本会自动构建所有演示程序并显示构建状态，方便一次性验证整个交叉编译环境。

### 验证t64支持

构建完成后，可以验证程序是否正确支持64位时间戳：

```bash
# 运行32位程序并检查时间支持
./build/test_length_32bit

# 对于Qt5程序，可以检查链接的库
ldd ./build/qt_demo_32bit | grep -E "(qt5|Qt5)"

# 验证库是否为32位但支持64位时间戳
file /usr/lib/i386-linux-gnu/libQt5Core.so.5.15.13
```

**预期结果**: 32位程序正常运行，链接t64版本的库，具备64位时间戳支持。

## 常见问题

### 基础编译问题

1. **编译错误**: 缺少交叉编译工具链
   - 解决: 安装 `gcc-multilib` 或 `gcc-i686-linux-gnu`

2. **运行错误**: "No such file or directory"
   - 解决: 安装 32 位运行时库 `libc6:i386`

3. **链接错误**: 找不到 32 位库文件
   - 解决: 确保安装了完整的 32 位开发库

### Qt5 相关问题

4. **Qt5 编译错误**: 缺少 Qt5 开发包
   - 解决: `sudo apt install qtbase5-dev qt5-qmake`

5. **Qt5 32位编译失败**: 缺少 32 位 Qt5 库
   - **Ubuntu 24.04 解决方案**:
   ```bash
   # 方案一：使用t64包（推荐）
   sudo apt install libqt5widgets5t64:i386 libqt5core5t64:i386 libqt5gui5t64:i386
   
   # 创建开发符号链接
   sudo ln -sf /usr/lib/i386-linux-gnu/libQt5Core.so.5 /usr/lib/i386-linux-gnu/libQt5Core.so
   sudo ln -sf /usr/lib/i386-linux-gnu/libQt5Gui.so.5 /usr/lib/i386-linux-gnu/libQt5Gui.so  
   sudo ln -sf /usr/lib/i386-linux-gnu/libQt5Widgets.so.5 /usr/lib/i386-linux-gnu/libQt5Widgets.so
   sudo ln -sf /usr/lib/i386-linux-gnu/libGL.so.1 /usr/lib/i386-linux-gnu/libGL.so
   ```

6. **qmake 32位配置困难**: qmake默认使用64位库路径
   - **本项目解决方案**: 使用手动编译方式，避开qmake复杂配置
   - **技术细节**: 
     - 使用64位头文件（与32位兼容）
     - 指定32位库路径和交叉编译器
     - 直接调用 `i686-linux-gnu-g++` 进行编译和链接

7. **Qt5 程序无法运行**: 缺少 GUI 环境
   - 解决: 确保有 X11 或 Wayland 显示环境，或使用 `export DISPLAY=:0`

### 时间戳相关问题 (2038年问题)

8. **什么是t64包？**
   - t64 = 64位时间戳支持，解决2038年32位time_t溢出问题
   - Ubuntu 24.04中所有Qt5包都已转换为t64版本
   - 对32位程序完全兼容，只是包名有"t64"后缀

9. **为什么不能使用传统包？**
   - Ubuntu 24.04已移除传统32位时间戳包（libqt5core5:i386等）
   - 旧包存在2038年溢出风险
   - t64包是唯一官方支持的解决方案
