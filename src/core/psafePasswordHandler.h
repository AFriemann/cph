/*
psafe password handler; used to handle password inputs.
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

#ifndef PSAFE_PASSWORD_HANDLER
#define PSAFE_PASSWORD_HANDLER

#include <gtk-3.0/gtk/gtk.h>
#include <gdk/gdkkeysyms.h>


GtkWidget* dialog;

int entry_callback (GtkWidget * widget, GdkEventKey* pKey,gpointer userdata);
const char *getPassword(void);

#endif
