/*
 *
 *
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

    arg = getopt_long (argc, argv, "cf:hp",
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

      case 'c':
        configWizard();
        return 0;

      case 'f':
        configFile = optarg; // TODO wird hier global hoch gezählt? Funktioniert das so?
        break;

      case 'h':
        fprintf(stdout, "%s", helpMsg);
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

  if (remainingParams < 2) {
    FILE* file = fopen(configFile, "r");
    keySize = readKeySizeFromFile(file);
    profile = (remainingParams == 0) ? readProfileFromFile(file) : argv[optind];
  } else {
    profile = argv[optind];
    keySize = atoi(argv[optind+1]);
  }

  // allocate space for password and set it
  char* password = (char*)calloc(maxParamSize, sizeof(char));

  if (FLAG_PWDFROMFILE) {
    if (file == NULL)
      file = fopen(configFile, "r");
    password = readPassFromFile(file);
  } else 
    password = getpass(passwordPrompt);

  // allocate space for key and set it
  char *keyBuffer = (char*)calloc(keySize, sizeof(char));
  createKey(keyBuffer, profile, password, keySize);

  // delete password and free space
  memset(password, 0, maxParamSize*sizeof(char));
  free(password);

  // output of key
  if (FLAG_PRINT)
    printf("Your Key: %s\n", keyBuffer);
  else
    keyToClipboard(keyBuffer);

  // delete key and free space
  memset(keyBuffer, 0, keySize*sizeof(char));
  free(keyBuffer);

  if (file != NULL) 
    fclose(file);

  return 0;
}

int readKeySizeFromFile(FILE *file) {
  return -1;
}

char* readProfileFromFile(FILE *file) {
  return NULL;
}

char* readPassFromFile(FILE *file) {
  return NULL;
}

void keyToClipboard(char* key) {
  printf("nothing yet");
}

void configWizard(void) {
  printf("This will guide you through the configuration process and create a new config file in your home folder.\n\
      There is, however, a config file available with this binary and you could also use that for manual configuration,\n\
      would you like to use that instead? [y]/n");
  if(tolower(getchar()) == 'y') {
    fprintf(stdout, "Copying config file to %s\n", configFile);
    // TODO
  }

  // TODO (standard key size, standard password)
  // additional factors for key creation
  printf("nothing else yet");
}

