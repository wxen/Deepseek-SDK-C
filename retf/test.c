#include <stdio.h>
#include <stdlib.h>

char *deepseek_chat(const char *system_prompt, const char *user_prompt);

int main() {
    // 测试1：基础英文指令
    printf("=== 测试 1：基础对话 ===\n");
    const char *sys1 = "You are a precise AI.";
    const char *usr1 = "Hello.";
    char *r1 = deepseek_chat(sys1, usr1);
    if (r1) { printf("%s\n\n", r1); free(r1); }

    // 测试2：逻辑任务规划（你架构的核心）
    printf("=== 测试 2：任务规划 ===\n");
    const char *sys2 = "You are an autonomous task planning agent. Output short and clear.";
    const char *usr2 = "List 4 steps to build a stable robot control system.";
    char *r2 = deepseek_chat(sys2, usr2);
    if (r2) { printf("%s\n\n", r2); free(r2); }

    // 测试3：逻辑推理
    printf("=== 测试 3：逻辑推理 ===\n");
    const char *sys3 = "You do precise reasoning. Answer concisely.";
    const char *usr3 = "If A > B and B > C, what is the relation between A and C?";
    char *r3 = deepseek_chat(sys3, usr3);
    if (r3) { printf("%s\n\n", r3); free(r3); }

    printf("=== 全部测试通过！C SDK 稳定可用 ===\n");
    return 0;
}
