#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define DEEPSEEK_API_KEY          "YOUR_API_KEY"
#define DEEPSEEK_MODEL            "deepseek-reasoner"//deepseek-coder;deepseek-chat;deepseek-reasoner
#define DEEPSEEK_BASE_URL         "https://api.deepseek.com/v1/chat/completions"
#define MAX_TOKENS                1024
#define TEMPERATURE               0.1

typedef struct {
    char *data;
    size_t size;
} ResponseBuf;

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    ResponseBuf *buf = (ResponseBuf *)userdata;

    char *tmp = realloc(buf->data, buf->size + realsize + 1);
    if (!tmp) return 0;

    buf->data = tmp;
    memcpy(buf->data + buf->size, ptr, realsize);
    buf->size += realsize;
    buf->data[buf->size] = 0;

    return realsize;
}

// 从 JSON 里提取 "content": 后面的字符串（极简版，够用）
static char *extract_content(const char *json) {
    const char *key = "\"content\":\"";
    const char *start = strstr(json, key);
    if (!start) return NULL;

    start += strlen(key);
    const char *end = strchr(start, '"');
    if (!end) return NULL;

    size_t len = end - start;
    char *res = malloc(len + 1);
    if (!res) return NULL;

    strncpy(res, start, len);
    res[len] = 0;
    return res;
}

char *deepseek_chat(const char *system_prompt, const char *user_prompt) {
    CURL *curl = curl_easy_init();
    if (!curl) return NULL;

    ResponseBuf buf = {0};
    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", DEEPSEEK_API_KEY);
    headers = curl_slist_append(headers, auth_header);

    char post_data[4096];
    snprintf(post_data, sizeof(post_data),
        "{\"model\":\"%s\",\"max_tokens\":%d,\"temperature\":%.2f,"
        "\"messages\":[{\"role\":\"system\",\"content\":\"%s\"},{\"role\":\"user\",\"content\":\"%s\"}]}",
        DEEPSEEK_MODEL,
        MAX_TOKENS,
        TEMPERATURE,
        system_prompt,
        user_prompt
    );

    curl_easy_setopt(curl, CURLOPT_URL, DEEPSEEK_BASE_URL);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    CURLcode res = curl_easy_perform(curl);
    char *content = NULL;

    if (res == CURLE_OK && buf.size > 0) {
        content = extract_content(buf.data);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(buf.data);
    return content;
}