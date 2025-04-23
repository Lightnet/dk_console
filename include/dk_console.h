//
// Author: David Kviloria
// ClangFormat: Mozilla
//
#if !defined(DK_CONSOLE_H)
#define DK_CONSOLE_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stdlib.h> // malloc

#define DK_UI_IMPLEMENTATION
#include "dk_ui.h"

#if !defined(LOG_SIZE)
// #define LOG_SIZE 1080 * 1080 // size of log buffer
#define LOG_SIZE 10000 // size of log buffer test
#endif

typedef struct
{
  char* text;
  int type;
} Log;

typedef struct
{
  int log_index;
  Log* logs;
  Rectangle ui;
  bool is_open;
  int scroll;
  KeyboardKey toggle_key;
} Console;

void DK_ConsoleInit(Console* console, int log_size);
void DK_ConsoleLog(Console* console, const char* text, int type);
void DK_ConsoleUpdate(Console* console, ImUI* imui, void (*callback)(const char*));
void DK_ConsoleClear(Console* console);
void DK_ConsoleShutdown(Console* console, int log_size);

#if defined(__cplusplus)
}
#endif

#endif // DK_CONSOLE_H