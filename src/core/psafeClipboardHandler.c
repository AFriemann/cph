/*
psafe clipboard handler; used to handle clipboard requests
Copyright (C) 2013 Aljosha Friemann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see [http://www.gnu.org/licenses/].
*/

#include "psafeClipboardHandler.h"

#include <gtk/gtk.h>
#include <string.h>

void copyStringToClipboard(const char *str) {
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

