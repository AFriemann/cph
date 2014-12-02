/*
cph input/output header file; used to handle user inputs.
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

#ifndef CPH_IO
#define CPH_IO

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 16
#define IO_MAX 64
#define BUFFER_SIZE IO_MAX * sizeof (char)

#ifdef __linux
#include <sys/mman.h>
#endif

#ifdef GTK
#include <gtk-3.0/gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#define CLIPBOARD_TIMEOUT 10000
#else
#include <termios.h>
struct termios oflags, nflags;
#endif

int init_buffer(char **buffer, const unsigned int zero);
int clear_buffer(char **buffer);

int input(char *buffer, const char *name);
void output(const char *buffer);

#endif
