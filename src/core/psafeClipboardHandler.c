#include "psafeClipboardHandler.h"

#include <gtk/gtk.h>
#include <string.h>

void copyStrToClipboard(const char *str) {
  gtk_init (0, NULL);

  g_timeout_add(10000, (GSourceFunc) clearClipboardAndExit, NULL);

	//GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkClipboard *primary= gtk_clipboard_get(GDK_SELECTION_PRIMARY);
	
	//gtk_clipboard_set_text(clipboard, str, strlen(str));
	gtk_clipboard_set_text(primary, str, strlen(str));

  gtk_main();

}

int clearClipboardAndExit(void) {
	//GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkClipboard *primary= gtk_clipboard_get(GDK_SELECTION_PRIMARY);

	//gtk_clipboard_clear(clipboard);
	//gtk_clipboard_set_text(clipboard, "", 0);
	gtk_clipboard_clear(primary);
	gtk_clipboard_set_text(primary, "", 0);
	
	gtk_main_quit();
	return 1;
}

