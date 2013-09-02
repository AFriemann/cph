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

#ifndef PSAFE_CLIPBOARD_HANDLER
#define PSAFE_CLIPBOARD_HANDLER

#include <gtk/gtk.h>
#include <string.h>

#define CLIPBOARD_TIMEOUT 10000

void str_to_clipboard(const char *str);
//int clear_clipboard_and_exit(void);

#endif
