#include "psafePasswordHandler.h"

int entry_callback (GtkWidget * widget, GdkEventKey* pKey,gpointer userdata) {
  gtk_main_quit(); 
  return 0;
}

char *getPassword(void) {
  if (isatty(1))
    return getpass("Please enter your password: ");
  else {
    gtk_init(0, NULL);

    GtkEntryBuffer *buffer = gtk_entry_buffer_new(NULL, -1);

    dialog = gtk_dialog_new();

    GtkWidget *content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

    GtkWidget *password_input = gtk_entry_new_with_buffer(buffer);
    gtk_entry_set_invisible_char(GTK_ENTRY (password_input), 0);
    //gtk_entry_set_input_purpose(password_input, GTK_INPUT_PURPOSE_PASSWORD);
    gtk_container_add (GTK_CONTAINER (content_area), password_input);

    g_signal_connect(dialog, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (password_input, "activate", G_CALLBACK (entry_callback), NULL);

    gtk_widget_show_all(dialog);

    gtk_main();

    return gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER (buffer));
  }
}

