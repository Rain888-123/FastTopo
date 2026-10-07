# FastTopo

![C](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-MIT-green)

A fast (maybe) topological sorting library written in pure C (C99, zero dependencies).

一个（也许）很快的纯 C 拓扑排序库（C99，零依赖）。

## Features / 特性

- Pure C, C99 standard, zero external dependencies

  纯 C 编写，C99 标准，零外部依赖
- Byte-key interface: `(ptr, len)` instead of fixed-length integers

  字节键接口：使用 `(ptr, len)` 而非定长整数
- Hash table normalization: maps arbitrary byte keys to dense indices

  哈希表归一化：将任意字节键映射为紧凑索引
- CSR graph storage for cache-friendly traversal

  CSR 图存储，遍历时缓存友好
- Kahn's algorithm for topological sort with cycle detection

  Kahn 算法拓扑排序，自带环检测

## Project Structure / 项目结构

```text
FastTopo/
├── include/
│   ├── ft_ht.h       # Hash table for key-to-index mapping / 键到索引映射的哈希表
│   ├── ft_dg.h       # Directed graph (CSR) / 有向图（CSR）
│   └── xxhash.h      # xxHash header / xxHash 头文件
├── src/
│   ├── ft_ht.c       # Hash table implementation / 哈希表实现
│   ├── ft_dg.c       # Graph construction / 建图
│   └── main.c        # Example usage / 使用示例
├── .gitattributes    # Force C language detection / 强制 C 语言识别
├── .gitignore        # Build artifacts / 编译产物忽略
├── CMakeLists.txt    # CMake build configuration / CMake 构建配置
├── LICENSE           # MIT License / MIT 许可证
├── NOTICE            # Third-party notices / 第三方声明
└── README.md         # This file / 本文件
```

## Build / 构建

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Status / 状态

Core features complete. Now optimizing.

核心功能已完成，正在进行优化。

## License / 许可证

MIT

## Third-Party / 第三方

[xxHash](https://github.com/Cyan4973/xxHash) — BSD 2-Clause License.

See [LICENSE-THIRD-PARTY](./LICENSE-THIRD-PARTY) for details.

详见 [LICENSE-THIRD-PARTY](./LICENSE-THIRD-PARTY)。
