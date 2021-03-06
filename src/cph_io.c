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

#ifdef GTK

GtkWidget *dialog;
GtkEntryBuffer *gtk_buffer;

/**
 * This method will send a message to their dialog window which can
 * be caught and used to exit respectively.
 */
int entry_callback(GtkWidget *widget, GdkEventKey *pKey, gpointer userdata)
{
    g_signal_emit_by_name(dialog, "destroy");
    return false;
}

/**
 * Clears the clipboard (sets content to an empty string) and exits gtk
 */
int clear_clipboard_and_exit(void)
{
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    GtkClipboard *primary = gtk_clipboard_get(GDK_SELECTION_PRIMARY);

    gtk_clipboard_clear(clipboard);
    gtk_clipboard_clear(primary);

    gtk_clipboard_set_text(clipboard, "", 0);
    gtk_clipboard_set_text(primary, "", 0);

    gtk_main_quit();

    return 0; // gtk convention
}

/**
 * Simple gtk error message window
 */
void gtk_error(const char* msg)
{
    gtk_init(0, NULL);

    dialog = gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
    GtkWidget *action_area  = gtk_dialog_get_action_area(GTK_DIALOG (dialog));

    GtkWidget *label = gtk_label_new(msg);
    gtk_container_add(GTK_CONTAINER (content_area), label);

    GtkWidget *ok_button = gtk_button_new_with_label("ok");
    gtk_container_add(GTK_CONTAINER (action_area), ok_button);

    g_signal_connect(dialog, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(ok_button, "clicked", G_CALLBACK (entry_callback), NULL);

    gtk_widget_show_all(dialog);

    gtk_main();
}

/**
 * Simple gtk password input window
 */
const char* gtk_input(const char *prompt)
{
    gtk_init(0, NULL);

    // TODO could we use an external buffer here or does it
    //      have to be this way?
    gtk_buffer = gtk_entry_buffer_new(NULL, -1);

    dialog = gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
    GtkWidget *password_input = gtk_entry_new_with_buffer(gtk_buffer);

    gtk_window_set_title(GTK_WINDOW (dialog), prompt);
    gtk_entry_set_visibility(GTK_ENTRY (password_input), false);
    //gtk_entry_set_invisible_char(GTK_ENTRY (password_input), 0);
    gtk_entry_set_input_purpose(GTK_ENTRY (password_input), GTK_INPUT_PURPOSE_PASSWORD);
    gtk_entry_set_max_length(GTK_ENTRY (password_input), IO_MAX);

    gtk_container_add(GTK_CONTAINER (content_area), password_input);

    g_signal_connect(dialog, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect(password_input, "activate", G_CALLBACK (entry_callback), NULL);

    gtk_widget_show_all(dialog);

    gtk_main();

    return gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER (gtk_buffer));
}

/**
 * Uses gtk_input method to retrieve user input
 */
int input(char* buffer, const char *name) {
    if (buffer == NULL || name == NULL) {
        return false;
    }

    if (strlen(buffer) != 0) {
        return true;
    }

    char prompt[128];
    snprintf(prompt, sizeof (prompt), "Please enter %s:", name);

    // TODO this does not feel very safe.
    strcpy(buffer, gtk_input(prompt));

    return true;
}

#ifdef __linux
/**
 * Exposes the given string to clipboard using gtk
 */
int output(const char* buffer)
{
    if (buffer == NULL) {
        return false;
    }

    gtk_init (0, NULL);

    // exit window and clear buffers after timeout
    g_timeout_add(CLIPBOARD_TIMEOUT, (GSourceFunc) clear_clipboard_and_exit, NULL);

    // write to primary and secondary selection
    GtkClipboard *clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    GtkClipboard *primary= gtk_clipboard_get(GDK_SELECTION_PRIMARY);

    gtk_clipboard_set_text(clipboard, buffer, strlen (buffer));
    gtk_clipboard_set_text(primary, buffer, strlen (buffer));

    gtk_main();

    return true;
}
#else
#error Platform not supported
#endif

#else

#ifdef __linux
/**
 * This method deactivates output of stdin and then reads user input up to
 * IO_MAX characters. Exceeding IO_MAX will result in program termination.
 */
int input(char* buffer, const char *name)
{
    if (buffer == NULL || name == NULL) {
        return false;
    }

    if (strlen(buffer) != 0) {
        return true;
    }

    unsigned int i;
    char c;

    // disable stdin echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag != ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags)) {
      perror("tcsetattr");
      return false;
    }

    printf("Please enter %s: ", name, stdout);

    i = 0;
    while ((c = getchar()) != '\n' && c != EOF){
        if (i < IO_MAX) {
            buffer[i++] = c;
        } else {
            return false;
        }
    }

    buffer[strlen(buffer)] = '\0';

    printf("\n", stdout);

    // re-enable stdin echo
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags)) {
      perror("tcsetattr");
      return false;
    }

    return true;
}
#else
#error Platform not supported
#endif

int output(const char* buffer)
{
    fprintf(stdout, "%s", buffer);
    return true;
}

#endif
