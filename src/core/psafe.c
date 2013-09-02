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

int main(int argc, char **argv) 
{
  int arg;

  while (1) 
  {
    /* getopt_long stores the option index here. */
    int option_index = 0;

    arg = getopt_long (argc, argv, "hl:p:", long_options, &option_index);

    /* Detect the end of the options. */
    if (arg == -1)
      break;

    switch (arg) 
    {
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
          break;
        //if (optarg)
        //  break;

      case 'h':
        fprintf(stderr, "%s", help_msg);
        return 0;

      case 'l':
        // read key size from console argument
        //char* tmp;
        key_size = strtol(argv[optind], NULL/*&tmp*/, 10);
        if (key_size > MAX_KEY_SIZE || key_size < 0)
          key_size = DEFAULT_KEY_SIZE;
        break;

      case 'p':
        // read password from console
        password = argv[optind];
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort(); 
    }
  }

  int remaining_params = argc - optind;

  if (remaining_params > 1)
  {
    fprintf(stderr, "%s", error_msg);
    return(1);
  }

  // set profile if not given
  if (remaining_params > 0) 
  {
    profile = argv[optind];
  }
  else 
  {
    profile = (char*)malloc(MAX_INPUT_SIZE*sizeof(char));
    get_input(profile, FALSE);
  }

  // set password
  if (password == NULL) 
  {
    password = (char*)calloc(MAX_INPUT_SIZE, sizeof(char));
    get_input(password, TRUE);
  }

  printf("profile is: %s\n", profile);
  printf("password is: %s with length: %d\n", password, (int)strlen(password));

  // allocate space for key and generate it
  key_buffer = (char*)calloc(key_size, sizeof(char));
  createKey(key_buffer, profile, password, key_size);

  // fork child process 
  pid_t childPID;

  childPID = fork();

  if(childPID >= 0) 
  { // fork was successful
    if(childPID == 0) 
    { // child process 
			/* initialize GTK */
			copy_string_to_clipboard(key_buffer);
			exit(0);
    } 
    else 
    { //Parent process
      exit(0);
    }
  } 
  else 
  { // fork failed
    printf("\n Fork failed, quitting!\n");
    return 1;
  }

  // delete password and profile and generated key from memory
  memset(password,    0, strlen(password)*sizeof(char));
  memset(profile,     0, strlen(profile)*sizeof(char));
  memset(key_buffer,  0, key_size*sizeof(char));
  free(key_buffer);
  printf("still foo");
  
  return 0;
}


