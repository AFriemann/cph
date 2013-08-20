/*
psafe main file, please read documentation for further information.
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


#include "psafe.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "%s", errorMsg);
    return 1;
  }

  int arg;

  while (1) {
    /* getopt_long stores the option index here. */
    int option_index = 0;

    arg = getopt_long (argc, argv, "h",
                    long_options, &option_index);

    /* Detect the end of the options. */
    if (arg == -1)
      break;

    switch (arg) {
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
          break;
        //if (optarg)
        //  break;

      case 'h':
        fprintf(stderr, "%s", helpMsg);
        return 0;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort(); 
    }
  }

  int remainingParams = argc - optind;

  if (remainingParams > 2){
    fprintf(stderr, "%s", errorMsg);
    return(1);
  }

  profile = argv[optind++];

  if (argv[optind] == NULL) {
    keySize = defaultKeySize;
  } else {
    char* tmp;
    int keySizeParam = strtol(argv[optind], &tmp, 10);
    // check for possible error 
    if (tmp == argv[optind] || keySizeParam > 1024) {
      fprintf(stderr, "Invalid input given for key size: %s! Setting to default (%i)\n", argv[optind], defaultKeySize);
      keySize = defaultKeySize;
    } else
      keySize = keySizeParam;
  }

  // allocate space for password and set it
  char* password = (char*)calloc(maxPwdSize, sizeof(char));
  password = getPassword();

  // allocate space for key and set it
  char *keyBuffer = (char*)calloc(keySize, sizeof(char));
  createKey(keyBuffer, profile, password, keySize);

  // delete password and free space
  memset(password, 0, maxPwdSize*sizeof(char));
  free(password);

  // output result
  fprintf(stdout, "%s", keyBuffer);

  // delete key and free space
  memset(keyBuffer, 0, keySize*sizeof(char));
  free(keyBuffer);
  
  return FLAG_ERROR;
}

int QuitProg(GtkWidget *widget, gpointer gdata){

    gtk_main_quit();
    return (FALSE);

}

char *getPassword(void) {
  if (isatty(1))
    return getpass(passwordPrompt);
  else {
    gtk_init(0, NULL);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_title(GTK_WINDOW(window), "psafe password prompt");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

    GtkWidget* eventBox = gtk_event_box_new();
    gtk_container_add (GTK_CONTAINER(window), eventBox);

    GtkWidget *password_input = gtk_entry_new();
    //gtk_entry_set_invisible_char(password_input, 0);
    gtk_container_add (GTK_CONTAINER (eventBox), password_input);

    gtk_widget_show (password_input);

    //gtk_container_add (GTK_CONTAINER (window_Widget), vBox_Widget);

    gtk_signal_connect(GTK_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return "foobar";
  }
}
