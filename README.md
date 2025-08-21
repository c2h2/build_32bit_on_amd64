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

```bash
# 编译 32 位版本
./build_64bit_to_32bit.sh

# 编译 64 位版本  
./build_64bit_to_64bit.sh

# 运行测试
./test_length_32bit  # 应该输出: Long size: 4
./test_length_64bit  # 应该输出: Long size: 8
```

## 常见问题

1. **编译错误**: 缺少交叉编译工具链
   - 解决: 安装 `gcc-multilib` 或 `gcc-i686-linux-gnu`

2. **运行错误**: "No such file or directory"
   - 解决: 安装 32 位运行时库 `libc6:i386`

3. **链接错误**: 找不到 32 位库文件
   - 解决: 确保安装了完整的 32 位开发库