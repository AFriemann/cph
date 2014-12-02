/*
cph input/output file; used to handle user inputs.
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

#include "cph_io.h"

#ifdef __linux

int init_buffer(char **buffer, const unsigned int zero)
{
    if (zero) {
        // TODO this is ugly..
        *buffer = calloc(IO_MAX, sizeof(char));
    } else {
        *buffer = malloc(BUFFER_SIZE);
    }

    return !mlock(*buffer, BUFFER_SIZE);
}

int clear_buffer(char **buffer)
{
    memset(*buffer, 0, BUFFER_SIZE);
    free(*buffer);

    return !munlock(*buffer, BUFFER_SIZE);
}

#else
#error Platform not supported
#endif

#ifdef GTK

GtkWidget *dialog;
GtkEntryBuffer *gtk_buffer;

int entry_callback(GtkWidget *widget, GdkEventKey *pKey, gpointer userdata)
{
    g_signal_emit_by_name(dialog, "destroy");
    return 0;
}

void gtk_error(const char* msg)
{
    gtk_init(0, NULL);

    dialog = gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
    GtkWidget *action_area  = gtk_dialog_get_action_area(GTK_DIALOG (dialog));

    GtkWidget *label = gtk_label_new(msg);
    gtk_container_add(GTK_CONTAINER (content_area), label);

    /* GtkWidget *ok_button = gtk_button_new_from_stock(GTK_STOCK_OK); */
    GtkWidget *ok_button = gtk_button_new_with_label("ok");
    gtk_container_add(GTK_CONTAINER (action_area), ok_button);

    g_signal_connect(dialog, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(ok_button, "clicked", G_CALLBACK (entry_callback), NULL);

    gtk_widget_show_all(dialog);

    gtk_main();
}

const char* gtk_input(const char *prompt)
{
    gtk_init(0, NULL);

    gtk_buffer = gtk_entry_buffer_new(NULL, -1);

    dialog = gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
    GtkWidget *password_input = gtk_entry_new_with_buffer(gtk_buffer);

    gtk_window_set_title(GTK_WINDOW (dialog), prompt);
    gtk_entry_set_visibility(GTK_ENTRY (password_input), FALSE);
    //gtk_entry_set_invisible_char(GTK_ENTRY (password_input), 0);
    gtk_entry_set_input_purpose(GTK_ENTRY (password_input), GTK_INPUT_PURPOSE_PASSWORD);

    gtk_container_add(GTK_CONTAINER (content_area), password_input);

    g_signal_connect(dialog, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(password_input, "activate", G_CALLBACK (entry_callback), NULL);

    gtk_widget_show_all(dialog);

    gtk_main();

    return gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER (gtk_buffer));
}

int clear_clipboard_and_exit(void)
{
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    GtkClipboard *primary = gtk_clipboard_get(GDK_SELECTION_PRIMARY);

    gtk_clipboard_clear(clipboard);
    gtk_clipboard_clear(primary);

    gtk_clipboard_set_text(clipboard, "", 0);
    gtk_clipboard_set_text(primary, "", 0);

    gtk_main_quit();

    return 0;
}

void str_to_clipboard(const char *str)
{
    gtk_init (0, NULL);

    g_timeout_add(CLIPBOARD_TIMEOUT, (GSourceFunc) clear_clipboard_and_exit, NULL);

    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    GtkClipboard *primary= gtk_clipboard_get(GDK_SELECTION_PRIMARY);

    gtk_clipboard_set_text(clipboard, str, strlen (str));
    gtk_clipboard_set_text(primary, str, strlen (str));

    gtk_main();
}

int input(char* buffer, const char *name)
{
    char prompt[128];
    snprintf(prompt, sizeof (prompt), "Please enter %s:", name);

    strcpy(buffer, gtk_input(prompt));

    return 0;
}

void output(const char* buffer)
{
    str_to_clipboard(buffer);
}

#else

int input(char* buffer, const char *name)
{
    // disable stdin echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag != ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags)) {
      perror("tcsetattr");
      return 0;
    }

    printf("Please enter %s: ", name);

    fgets(buffer, IO_MAX, stdin);

    unsigned int length = strlen(buffer);

    // delete newline char
    if (buffer[length - 1] == '\n') {
      buffer[length - 1] = 0;
    }

    printf("\n");

    // enable stdin echo
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags)) {
      perror("tcsetattr");
      return 0;
    }

    return 1;
}

void output(const char* buffer)
{
    fprintf(stdout, "%s", buffer);
}

#endif
