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

#include "cph_input_handler.h"

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

    GtkWidget *ok_button = gtk_button_new_from_stock(GTK_STOCK_OK);
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

void get_input(char* buffer, const char *name, const int max_input_length, const int with_gui)
{
    char prompt[128];
    snprintf(prompt, sizeof (prompt), "Please enter %s:", name);

    const char* temp;

    if (!with_gui)
    {
        while (1)
        {
            temp = getpass(prompt);
            if (strlen (temp) > max_input_length)
                fprintf(stderr, "The given input exceeded %i characters! Please try again.\n", max_input_length);
            else
                break;
        }
        strcpy(buffer, temp);
    }
    else
    {
        while (1)
        {
            temp = gtk_input(prompt); // always use password input
            if (strlen (temp) > max_input_length)
            {
                char msg_buffer[128];
                snprintf(msg_buffer, sizeof (msg_buffer), "The given input exceeded %i characters! Please try again.", max_input_length);
                gtk_error(msg_buffer);
            }
            else
            {
                break;
            }
        }
        strcpy(buffer, temp);
        gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER (gtk_buffer), 0, -1);
    }
}

