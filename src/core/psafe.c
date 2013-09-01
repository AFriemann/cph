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

    arg = getopt_long (argc, argv, "hl:",
                    long_options, &option_index);

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
        fprintf(stderr, "%s", helpMsg);
        return 0;

      case 'l':
        // read key size from console argument
        //char* tmp;
        keySize = strtol(argv[optind], NULL/*&tmp*/, 10);
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort(); 
    }
  }

  int remainingParams = argc - optind;

  /*
  if ( remainingParams > 2 ){
    fprintf(stderr, "%s", errorMsg);
    return(1);
  }

  profile = argv[optind++]; remainingParams--;
  password = getPassword(); // calls password function

  if (remainingParams == 0) {
    keySize = defaultKeySize;
  } else {
    // read key size from console argument
    char* tmp;
    int keySizeParam = strtol(argv[optind], &tmp, 10);
    // check for possible error 
    if (tmp == argv[optind] || keySizeParam > 1024) {
      fprintf(stderr, "Invalid input given for key size: %s! Setting to default (%i)\n", argv[optind], defaultKeySize);
      keySize = defaultKeySize;
    } else
      keySize = keySizeParam;
  }
  */

  if ( remainingParams == 0 ) 
  {
    keySize = (keySize != NULL) ? keySize : defaultKeySize;
    profile = (profile != NULL) ? profile : getProfile();
    password = (password != NULL) ? password : getPassword();
  } 
  else if ( remainingParams == 1 && !( profile != NULL ) ) 
  {
    keySize = (keySize != NULL) ? keySize : defaultKeySize;
    profile = argv[optind];
    password = (password != NULL) ? password : getPassword();
  } 
  else 
  {
    fprintf(stderr, "%s", errorMsg);
    return(1);
  }

  // allocate space for key and generate it
  char *keyBuffer = (char*)calloc(keySize, sizeof(char));
  createKey(keyBuffer, profile, password, keySize);

  // fork child process 
  pid_t childPID;

  childPID = fork();

  if(childPID >= 0) 
  { // fork was successful
    if(childPID == 0) 
    { // child process 
			/* initialize GTK */
			gtk_init (0, NULL);

			copyStringToClipboard(keyBuffer);
	
			g_timeout_add(10000,(GSourceFunc) clearClipboardAndExit,NULL);
	
			gtk_main();
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
  memset(password, 0, strlen(password)*sizeof(char));
  memset(profile, 0, strlen(profile)*sizeof(char));
  memset(keyBuffer, 0, keySize*sizeof(char));
  free(keyBuffer);
  
  return FLAG_ERROR;
}


