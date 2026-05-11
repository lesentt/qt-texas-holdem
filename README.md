# DZPoker

一个使用 C++ 与 Qt 开发的单机版双人德州扑克游戏。

## 项目简介

本项目实现了一个本地双人对战的德州扑克图形界面程序，包含：

- 游戏开始界面
- 玩家与 AI 对战
- 发牌、下注、公共牌展示
- 手牌选择与胜负判断

## 开发环境

- C++17
- Qt 6
- CMake 3.16 及以上
- Windows
- MinGW 64-bit

说明：项目此前在 Qt Creator + Qt 6.9.0 MinGW 64-bit 环境下开发。

## 构建方式

### 使用 Qt Creator

1. 用 Qt Creator 打开项目根目录下的 `CMakeLists.txt`
2. 选择已安装的 Qt Kit，例如 `Desktop Qt 6.x MinGW 64-bit`
3. 配置并构建项目
4. 运行生成的 `DZPoker`

### 使用命令行

```bash
cmake -S . -B build
cmake --build build
```

如果本机安装了多个 Qt 版本，可能需要额外指定 Qt 的 CMake 路径。

## 项目结构

```text
DZPoker/
├─ CMakeLists.txt
├─ main.cpp
├─ startgame.cpp / startgame.h / startgame.ui
├─ gaming.cpp / gaming.h / gaming.ui
├─ banker.cpp / banker.h
├─ player.cpp / player.h
├─ deck.cpp / deck.h
├─ poker.cpp / poker.h
├─ game.cpp / game.h
├─ res.qrc
├─ resource/
└─ icon.ico
```

## 资源文件

项目使用 Qt 资源系统管理图片资源，资源入口文件为：

- `res.qrc`

图片素材位于：

- `resource/`

## 当前说明

- 本仓库保留了项目源码、界面文件和资源文件
- 项目中可能仍存在历史开发残留文件，后续可继续清理

## 文档

仓库中附带了一份中文说明文档：

- `德州扑克.docx`

## 许可证

当前仓库未附加开源许可证。如需公开开源发布，建议在上传前补充 `LICENSE` 文件。
