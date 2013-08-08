#ifndef CLIPBOARD_HANDLER
#define CLIPBOARD_HANDLER

#ifdef _WIN32
#include <windows.h>
#endif

int handleSelectionRequest(const int timeout);
int clearClipboard(void);
int writeStringToClipboard(const char *string);

#endif
