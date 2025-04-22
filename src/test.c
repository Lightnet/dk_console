//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#include "raylib.h"
#include "raymath.h"
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

#include "dk_console.h"
#define DK_CONSOLE_EXT_COMMAND_IMPLEMENTATION
#include "dk_command.h"

static Console console = {.toggle_key = KEY_TAB};
static Console* console_global_ptr = NULL;

void CustomLog(int msgType, const char* text, va_list args);

typedef struct {
    double* data;
    int capacity;
    int size;
} Stack;

void Stack_Init(Stack* s)
{
    s->capacity = 4;
    s->size = 0;
    s->data = malloc(s->capacity * sizeof(double));
}

void Stack_Push(Stack* s, double value)
{
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(double));
    }
    s->data[s->size++] = value;
}

double Stack_Pop(Stack* s)
{
    return s->data[--s->size];
}

int Stack_Empty(Stack* s)
{
    return s->size == 0;
}

double evaluateRPN(const char* expr)
{
    Stack s;
    Stack_Init(&s);

    while (*expr) {
        while (isspace(*expr)) {
            ++expr;
        }

        if (isdigit(*expr) || ((*expr == '+' || *expr == '-') && isdigit(*(expr + 1)))) {
            char* end;
            double value = strtod(expr, &end);
            expr = end;
            Stack_Push(&s, value);
        } else {
            double right = Stack_Pop(&s);
            double left = Stack_Pop(&s);

            switch (*expr) {
                case '+':
                    Stack_Push(&s, left + right);
                    break;
                case '-':
                    Stack_Push(&s, left - right);
                    break;
                case '*':
                    Stack_Push(&s, left * right);
                    break;
                case '/':
                    Stack_Push(&s, left / right);
                    break;
                default:
                    CustomLog(LOG_ERROR, "Invalid Operation", NULL);
                    return 0;
            }

            ++expr;
        }
    }

    double result = Stack_Pop(&s);
    if (!Stack_Empty(&s)) {
        CustomLog(LOG_ERROR, "Invalid expression", NULL);
        return 0;
    }

    return result;
}

void CustomLog(int msgType, const char* text, va_list args)
{
    assert(console_global_ptr != NULL);
    static char buffer[1024] = {0};

    char timeStr[64] = {0};
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    vsprintf(buffer, text, args);

    char finalBuffer[1024] = {0};
    sprintf(finalBuffer, "%s %s", timeStr, buffer);

    const char* msgTypeStr = "Unknown";
    switch (msgType) {
        case LOG_DEBUG:
            msgTypeStr = "(Debug)";
            break;
        case LOG_INFO:
            msgTypeStr = "(Info)";
            break;
        case LOG_WARNING:
            msgTypeStr = "(Warning)";
            break;
        case LOG_ERROR:
            msgTypeStr = "(Error)";
            break;
        case LOG_FATAL:
            msgTypeStr = "(Fatal)";
            break;
    }

    char finalBuffer2[1024] = {0};
    sprintf(finalBuffer2, "%s %s", msgTypeStr, finalBuffer);

    DK_ConsoleLog(console_global_ptr, finalBuffer2, msgType);
}

void echo(const char* argv)
{
    CustomLog(LOG_INFO, argv, NULL);
}

void clear(const char* argv)
{
    DK_ConsoleClear(console_global_ptr);
}

void help(const char* args)
{
    DK_ExtCommand* command_list = DK_ExtGetCommandsList();
    if (args != NULL && strlen(args) > 0) {
        for (int i = 0; i < DK_COMMAND_SIZE; i++) {
            if (command_list[i].name != NULL) {
                if (strcmp(command_list[i].name, args) == 0) {
                    CustomLog(LOG_INFO, TextFormat("\t\t`%s`\t\t%s\n", command_list[i].name, command_list[i].help), NULL);
                    if (command_list[i].argc > 0) {
                        CustomLog(LOG_INFO, TextFormat("\t\ttakes %d argument(s)\n", command_list[i].argc), NULL);
                    }
                    break;
                }
            }
        }
        return;
    } else {
        CustomLog(LOG_INFO, "******************** HELP ********************", NULL);
        for (int i = 0; i < DK_COMMAND_SIZE; i++) {
            if (command_list[i].name != NULL) {
                CustomLog(LOG_INFO, TextFormat("\t\t`%s`\t\t%s\n", command_list[i].name, command_list[i].help), NULL);
                if (command_list[i].argc > 0) {
                    CustomLog(LOG_INFO, TextFormat("\t\ttakes %d argument(s)\n", command_list[i].argc), NULL);
                }
                CustomLog(LOG_INFO, "----------------------------------------------", NULL);
            }
        }
    }
}

void mathEval(const char* args)
{
    double result = evaluateRPN(args);
    CustomLog(LOG_INFO, TextFormat("Eval(%s) = %f", args, result), NULL);
}

#if !defined(PLATFORM_WEB)
void shell(const char* args)
{
    FILE* fp;
    char path[1035];

    fp = popen(args, "r");
    if (fp == NULL) {
        CustomLog(LOG_ERROR, "Sh: Failed to execute command", NULL);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        CustomLog(LOG_INFO, path, NULL);
    }

    pclose(fp);
}
#endif

void console_handler(const char* command)
{
    char* command_buff = (char*)malloc(strlen(command) + 1);
    strcpy(command_buff, command);
    command_buff[strlen(command)] = '\0';

    char* token = strtok(command_buff, " ");

    char* message_buff = (char*)malloc(strlen(command) + 1);
    strcpy(message_buff, command);
    message_buff[strlen(command)] = '\0';

    char* message = strstr(message_buff, token) + strlen(token);
    while (*message == ' ') {
        message++;
    }

    if (!DK_ExtCommandExecute(token, message)) {
        CustomLog(LOG_ERROR, TextFormat("Unknown command `%s`", command), NULL);
    }

    free(command_buff);
    free(message_buff);
}

int main(void)
{
    SetTraceLogCallback(CustomLog);

    DK_ExtCommandInit();
    DK_ExtCommandPush("echo", 1, "Prints a provided message in the console `echo Hello World`", &echo);
    DK_ExtCommandPush("clear", 0, "Clears the console buffer", &clear);
    DK_ExtCommandPush("help", 1, "Shows the available commands and/or specific one `help <command_name>`", &help);
    DK_ExtCommandPush("calc", -1, "Evaluates a mathematical expression `calc 2 2 +`", &mathEval);
#if !defined(PLATFORM_WEB)
    DK_ExtCommandPush("sh", 1, "Executes a shell command `sh ls -la`", &shell);
#endif

    static ImUI imui;
    imui.theme = &DK_ImUISolarizedTheme;
    imui.style = &DK_ImUIDefaultStyle;

    const int screenWidth = 1280;
    const int screenHeight = 720;

    console_global_ptr = &console;

    DK_ConsoleInit(console_global_ptr, LOG_SIZE);
    InitWindow(screenWidth, screenHeight, "Dev Console");

    SetTargetFPS(60);

    Font customFont = LoadFont("Resources/font/JetBrainsMono-Regular.ttf"); // Replace with actual path
    if (customFont.texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load font!");
        customFont = GetFontDefault();
    }
    imui.font = &customFont;
    SetTextureFilter(imui.font->texture, TEXTURE_FILTER_BILINEAR);

    // Add initial test logs
    CustomLog(LOG_DEBUG, "Debug message", NULL);
    CustomLog(LOG_INFO, "Info message", NULL);
    CustomLog(LOG_WARNING, "Warning message", NULL);
    CustomLog(LOG_ERROR, "Error message", NULL);
    CustomLog(LOG_FATAL, "Fatal message", NULL);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(Fade(BLACK, 0.5f));

        const char* text = "Press TAB to toggle the console";
        Vector2 position = {20.0f, 20.0f};
        DrawTextEx(*imui.font, text, position, 20.0f, 1.0f, GRAY);

        DK_ConsoleUpdate(console_global_ptr, &imui, console_handler);
        EndDrawing();
    }

    DK_ConsoleShutdown(console_global_ptr, LOG_SIZE);
    UnloadFont(customFont);
    CloseWindow();

    return 0;
}