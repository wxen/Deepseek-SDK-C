# DeepSeek C SDK

深度求索（DeepSeek）官方 Chat Completions API 的 C 语言实现，依赖极少，解析完整可用。

## 特性

- **极简依赖**：仅依赖 libcurl
- **完整实现**：支持 system + user 双角色消息
- **轻量解析**：内置 JSON `content` 字段提取
- **多模型**：支持 `deepseek-chat`、`deepseek-coder`、`deepseek-reasoner`

## 依赖

- GCC（或兼容 C 编译器）
- [libcurl](https://curl.se/libcurl/)

### 安装 libcurl

```bash
# Ubuntu/Debian
sudo apt install libcurl4-openssl-dev

# Fedora/RHEL
sudo dnf install libcurl-devel

# macOS
brew install curl
```

## 快速开始

### 1. 配置 API Key

编辑 `deepseek_sdk.c`，将 `DEEPSEEK_API_KEY` 替换为你的 [DeepSeek API Key](https://platform.deepseek.com/)：

```c
#define DEEPSEEK_API_KEY          "sk-xxxxxxxxxxxxxxxx"
```

### 2. 编译与运行

```bash
gcc -o test test.c deepseek_sdk.c -lcurl
./test
```

### 3. 可选：切换模型

在 `deepseek_sdk.c` 中修改 `DEEPSEEK_MODEL`：

```c
#define DEEPSEEK_MODEL  "deepseek-chat"      // 通用对话
#define DEEPSEEK_MODEL  "deepseek-coder"     // 代码专用
#define DEEPSEEK_MODEL  "deepseek-reasoner"  // 推理增强
```

## API 使用

```c
#include "deepseek_sdk.c"  // 或单独编译后链接

char *deepseek_chat(const char *system_prompt, const char *user_prompt);
```

- **参数**：`system_prompt` 系统提示词，`user_prompt` 用户输入
- **返回**：模型回复文本（需调用方 `free()` 释放），失败返回 `NULL`

### 示例

```c
char *reply = deepseek_chat("You are a helpful assistant.", "Hello!");
if (reply) {
    printf("%s\n", reply);
    free(reply);
}
```

## 项目结构

```
.
├── deepseek_sdk.c   # SDK 核心实现
├── test.c           # 演示与快速测试
└── README.md
```

## 许可证

MIT License
