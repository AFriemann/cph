/*
cph key algorithm source, generates keys.
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

#include "cph_key.h"

int generate_key(char *buffer, const char *profile, const char *password, const int length, const unsigned int algorithm, const unsigned int abc)
{
    // Version check should be the very first call because it
    // makes sure that important subsystems are intialized.
    if (!gcry_check_version (GCRYPT_VERSION))
    {
        fputs ("libgcrypt version mismatch\n", stderr);
        return 2;
    }

    char *alphabet;

    switch (abc)
    {
        case 1: // extended
            alphabet =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+/$-_"
                        "|&%*=:!#~@><.,^";
            break;
        default: // lowercase, uppercase, numbers
            alphabet =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+/$-_";
            break;
    }

    // process input
    int input_length = strlen(profile) + strlen(password);

    // prepare hash buffer
    int hash_size = gcry_md_get_algo_dlen( algorithm ) * sizeof (unsigned char);
    char* hash = calloc( gcry_md_get_algo_dlen( algorithm ), sizeof (unsigned char));

    if (hash == NULL)
        return 0;

    if (mlock(hash, hash_size))
    {
        free(hash);
        return 0;
    }

    snprintf(hash, (input_length + 1) * sizeof (char), "%s%s", profile, password);

    /* init libgcrypt */

    // We don't want to see any warnings, e.g. because we have not yet
    // parsed program options which might be used to suppress such
    // warnings.
    gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);

    // Allocate a pool of 16k secure memory.  This make the secure memory
    // available and also drops privileges where needed.
    gcry_control(GCRYCTL_INIT_SECMEM, 16384, 0);

    // It is now okay to let Libgcrypt complain when there was/is
    // a problem with the secure memory.
    gcry_control(GCRYCTL_RESUME_SECMEM_WARN);

    // Tell Libgcrypt that initialization has completed.
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    /* calculate hash and write to hash buffer */

    gcry_md_hash_buffer( algorithm, hash, hash, strlen(hash) );

    // fit length to given
    int i;
    for ( i = 0; i < length && i < hash_size; i++) 
    {
        char c = (alphabet[(((unsigned int) hash[i]) % strlen(alphabet))]);
        sprintf( buffer++, "%c", c );
    }

    memset(hash, 0, hash_size);
    munlock(hash, hash_size);

    free(hash);

    // TODO do we have to do anything with the secure memory after this?

    return 1;
}
