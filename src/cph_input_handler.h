/*
cph input handler; used to handle user inputs.
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

#ifndef CPH_INPUT_HANDLER
#define CPH_INPUT_HANDLER

#include <gtk-3.0/gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>

//int entry_callback (GtkWidget * widget, GdkEventKey* pKey,gpointer userdata);
//const char* gtk_input(const int is_password);
void get_input(char *buffer, const char *name, const int max_input_length, const int with_gui);

#endif
