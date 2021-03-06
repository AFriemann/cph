/*
cph args file, please read documentation for further information.
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

#include "cph_args.h"

static const Config DEFAULT_CONFIG = { 0, 0, 0, DEFAULT_LENGTH, DEFAULT_ALGORITHM };

/**
 * Matches a string to the corresponding hash alrogithm.
 * Uses DEFAULT_ALGORITHM if no match was found.
 */
unsigned int parse_algo(char *arg)
{
    if ( strncmp(optarg, "tiger", 50)  == 0 ) { return tiger; }
    else if ( strncmp(optarg, "tiger1", 50) == 0 ) { return tiger1; }
    else if ( strncmp(optarg, "tiger2", 50) == 0 ) { return tiger2; }
    else if ( strncmp(optarg, "sha256", 50) == 0 ) { return sha256; }
    else if ( strncmp(optarg, "sha512", 50) == 0 ) { return sha512; }
    else if ( strncmp(optarg, "whirlpool", 50) == 0 ) { return whirlpool; }

    fprintf(stderr, "algorithm %s not available, using default (%u)\n", optarg, DEFAULT_ALGORITHM);
    return DEFAULT_ALGORITHM;
}

/**
 * This method is used to parse arguments from command line and will return
 * a Config struct to be conveniently used by cph.
 * It has to be called with pre allocated buffers for word/salt.
 */
Config parse_args(int argc, char *argv[], char *word, char *salt)
{
    char arg;
    int length_input, remaining_params, option_index;

    Config result = DEFAULT_CONFIG;

    if (word == NULL || salt == NULL) {
        result.ERR = 1;
    }

    while (! result.ERR)
    {
        /* getopt_long stores the option index here. */
        option_index = 0;

        arg = getopt_long (argc, argv, "a:ceghl:s:vw:", long_options, &option_index);

        /* Detect the end of the options. */
        if (arg == -1) { break; }

        switch (arg)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0) { break; }
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'c':
                fprintf(stdout, "%s\n", license);
                exit(0);

            case 'h':
                fprintf(stdout, "%s\n", help_msg);
                exit(0);

            case 'v':
                fprintf(stdout, "v%s\n", VERSION);
                exit(0);

            case 'a':
                result.ALGORITHM = parse_algo(optarg);
                break;

            case 'e':
                result.EXTENDED = 1;
                break;

            case 'l':
                // read key length from console argument
                length_input = strtol(optarg, NULL/*&tmp*/, 10); // TODO?
                if (length_input >= 0) {
                    result.LENGTH = length_input;
                }
                break;

            case 's':
                // read password from console
                if (strlen(optarg) > IO_MAX) {
                    printf("salt input length > %d\n", IO_MAX);
                    result.ERR = 1;
                }
                else { strcpy(salt, optarg); }
                break;

            case 'w':
                // read password from console
                if (strlen(optarg) > IO_MAX) {
                    printf("word input length > %d\n", IO_MAX);
                    result.ERR = 1;
                }
                else { strcpy(word, optarg); }
                break;

            case '?':
                /* getopt_long already printed an error message. */
                break;

            default:
                abort();
        }
    }

    remaining_params = argc - optind;

    if (remaining_params > 0) {
        fprintf(stderr, "%s\n", error_msg);
        result.ERR = 1;
    }

    return result;
}
