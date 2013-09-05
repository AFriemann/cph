/*
psafe input handler; used to handle user inputs.
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

#include "psafeInputHandler.h"

int 
entry_callback (GtkWidget *widget, GdkEventKey *pKey, gpointer userdata) 
{
  g_signal_emit_by_name(dialog, "destroy");
  return 0;
}

void 
gtk_error(const char* msg)
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

const char* 
gtk_input(const int is_password) 
{
  gtk_init(0, NULL);

  gtk_buffer = gtk_entry_buffer_new(NULL, -1);

  dialog = gtk_dialog_new();

  GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
  GtkWidget *password_input = gtk_entry_new_with_buffer(gtk_buffer);

  if (is_password)
  { 
    gtk_window_set_title(GTK_WINDOW (dialog), "password");
    gtk_entry_set_visibility(GTK_ENTRY (password_input), FALSE);
    //gtk_entry_set_invisible_char(GTK_ENTRY (password_input), 0);
    gtk_entry_set_input_purpose(GTK_ENTRY (password_input), GTK_INPUT_PURPOSE_PASSWORD);
  }  
  else
  { 
    gtk_window_set_title(GTK_WINDOW (dialog), "profile"); 
  }

  gtk_container_add(GTK_CONTAINER (content_area), password_input);

  g_signal_connect(dialog, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect(password_input, "activate", G_CALLBACK (entry_callback), NULL);

  gtk_widget_show_all(dialog);

  gtk_main();

  return gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER (gtk_buffer));
}

void 
get_input(char* buffer, const int is_password, const int max_input_length) {
  if (isatty(1))
  {
    if (is_password) 
    {  
      const char* temp;
      while (TRUE)
      {  
        temp = getpass("Please enter your password: ");
        if (strlen (temp) > max_input_length)
          fprintf(stderr, "The given password exceeded %i characters! Please try again.\n", max_input_length);
        else
          break;
      }      
      strcpy(buffer, temp);
    }    
    else
    {
      fprintf(stdout, "%s", "Please enter the profile name: ");
      fgets(buffer, max_input_length, stdin);
    }
  }
  else
  {
    const char* temp; 
    while (TRUE) 
    {
      temp = gtk_input(is_password);
      if (strlen (temp) > max_input_length)
      {   
        char msg_buffer[128];
        snprintf(msg_buffer, sizeof (msg_buffer), "%s %i %s", "The given password exceeded", max_input_length, "characters!");
        gtk_error(msg_buffer);
      }      
      else
        break;
    }
    strcpy(buffer, gtk_input(is_password));
    gtk_entry_buffer_delete_text(GTK_ENTRY_BUFFER (gtk_buffer), 0, -1);
  }
}

