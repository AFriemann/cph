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

void 
clear_buffers(void) 
{
  memset(password, 0, strlen (password) * sizeof(char));
  memset(profile, 0, strlen (profile) * sizeof(char));
  memset(key_buffer, 0, key_size * sizeof(char));
  free(password);
  free(profile);
  free(key_buffer);
}

int 
main(int argc, char **argv) 
{
  int arg;
  profile     = malloc(INPUT_MAX * sizeof(char));
  password    = malloc(INPUT_MAX * sizeof(char));
  key_buffer  = calloc(key_size, sizeof(char));

  while (1) {
    /* getopt_long stores the option index here. */
    int option_index = 0;

    arg = getopt_long (argc, argv, "chl:p:v", long_options, &option_index);

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

      case 'c':
        fprintf(stdout, "%s\n", license);
        return 0;

      case 'h':
        fprintf(stdout, "%s\n", help_msg);
        return 0;

      case 'l':
        // read key size from console argument
        key_size = strtol(optarg, NULL/*&tmp*/, 10);
        if (key_size > KEY_MAX || key_size < 0)
          key_size = DEFAULT_KEY_SIZE;
        break;

      case 'p':
        // read password from console
        strcpy(password, optarg);
        break;

      case 'v':
        fprintf(stdout, "%G\n", VERSION);
        return 0;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort(); 
    }
  }

  int remaining_params = argc - optind;

  if (remaining_params > 1) {
    fprintf(stderr, "%s\n", error_msg);
    return(1);
  }

  // set profile if not given
  if (remaining_params > 0) 
    strcpy(profile, argv[optind]);
  else 
    get_input(profile, FALSE, INPUT_MAX);

  // set password
  if (strlen(password) == 0)
    get_input(password, TRUE, INPUT_MAX);

  // generate key
  create_key(key_buffer, profile, password, key_size);

  if (FLAG_PRINT) {
    fprintf(stdout, "%s\n", key_buffer); 
    clear_buffers();
    return 0;
  }

  // fork child process 
  pid_t childPID;

  childPID = fork();

  if(childPID >= 0) { // fork was successful
    if(childPID == 0) { // child process 
			/* initialize GTK */
			str_to_clipboard(key_buffer);
      
      memset(key_buffer, 0, key_size * sizeof(char));
      free(key_buffer);

			exit(0);
    } 
    else { //Parent process
      memset(password, 0, strlen (password) * sizeof(char));
      memset(profile, 0, strlen (profile) * sizeof(char));
      free(password);
      free(profile);
      exit(0);
    }
  } 
  else { // fork failed
    fprintf(stderr, "\n Fork failed, quitting!\n");
    return 1;
  }
  
  return 0;
}


