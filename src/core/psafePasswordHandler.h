#ifndef PSAFE_PASSWORD_HANDLER
#define PSAFE_PASSWORD_HANDLER

#include <gtk-3.0/gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

int entry_callback (GtkWidget * widget, GdkEventKey* pKey,gpointer userdata);
char *getPassword(void);

#endif
