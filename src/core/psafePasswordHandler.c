#include "psafePasswordHandler.h"

int entry_callback (GtkWidget * widget, GdkEventKey* pKey,gpointer userdata) {
  gtk_main_quit(); 

  return 0;
}

char *getPassword(void) {
  if (isatty(1))
    return getpass("Please enter your password: ");
  else {
    char *password;

    gtk_init(0, NULL);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(window), 200, 0);
    gtk_window_set_title(GTK_WINDOW(window), "psafe password prompt");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

    GtkWidget* eventBox = gtk_event_box_new();
    gtk_container_add (GTK_CONTAINER(window), eventBox);

    GtkWidget *password_input = gtk_entry_new();
    //gtk_entry_set_invisible_char(password_input, 0);
    //gtk_entry_set_input_purpose(password_input, GTK_INPUT_PURPOSE_PASSWORD);
    gtk_container_add (GTK_CONTAINER (eventBox), password_input);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect (password_input, "activate", G_CALLBACK (entry_callback), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return gtk_entry_get_text(GTK_ENTRY(password_input));
  }
}

