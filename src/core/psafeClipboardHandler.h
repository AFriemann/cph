#ifndef PSAFE_CLIPBOARD_HANDLER
#define PSAFE_CLIPBOARD_HANDLER

#include <gtk/gtk.h>
#include <string.h>

void copyStringToClipboard(char *string);
int clearClipboardAndExit(void);

#endif
