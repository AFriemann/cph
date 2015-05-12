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
#include <stdbool.h>

#define DEFAULT_LENGTH 16
#define IO_MAX 32
#define BUFFER_SIZE (IO_MAX + 1) * sizeof (char)

#ifdef __linux
#include <sys/mman.h>
#endif

#ifdef GTK

#include <gtk-3.0/gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#define CLIPBOARD_TIMEOUT 10000

#else

#ifdef __linux
#include <termios.h>
struct termios oflags, nflags;
#else
#error Platform not supported
#endif

#endif

#define EXIT_OK 0
#define EXIT_MEM_ERR 1
#define EXIT_INPUT_ERR 2
#define EXIT_LIBGRCYPT_ERR 3
#define EXIT_KEY_ERROR 4

int init_buffer(char **buffer, const unsigned int zero);
int clear_buffer(char **buffer);

int input(char *buffer, const char *name);
int output(const char *buffer);

#endif
