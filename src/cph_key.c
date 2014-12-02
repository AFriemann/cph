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

char *base64  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "0123456789+/";
char *baseE91 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~\"";

char *alphabet;

char encode(char a)
{
    int i;
    for (i = 0; i < strlen (alphabet); i++)
    {
        if (a == alphabet[i]) { return a; }
    }

    return alphabet[(unsigned int) a % strlen(alphabet)];
}

void str_encode(char *buffer, char* string, const unsigned int string_size)
{
    int i;
    for ( i = 0; i < string_size; i ++)
    {
        buffer[i] = encode(string[i]);
    }
}

/**
 * This function splits the digest into equal parts and computes their XOR. Further remaining characters will be stripped:
 *
 * "abcdefghijklmnop" has size 16
 * length 6 will result in a slice size of 8, since 16 % 6 !=0 and 16 % 7 != 0 but 16 % 8 == 0
 *
 * now we split the string into pieces [abcdefgh] and [ijklmnop] and XOR them
 * "abcdefgh" ^ "ijklmnop" = "12345678"
 *
 * and strip the remaining characters: "123456"
 *
 * That way we retain as much information as possible while keeping the password length variable.
 *
 * TODO: verify that this actually works and makes sense
 */
void zip_encode(char* buffer, char* string, const unsigned int string_size, const unsigned int length)
{
    // find optimal slice length
    unsigned int slice_size, slice_count;
    if (length <= string_size / 2) {
        slice_size = length;
        while ( ( string_size % slice_size ) != 0 ) { slice_size++; }
    } else {
        slice_size = string_size;
    }

    slice_count = string_size / slice_size;

    int i,j;

    // XOR string slices
    for (i = 1; i < slice_count; i++)
    {
        for (j = 0; j < slice_size; j++)
        {
            string[j] ^= string[j + (i * slice_size)];
        }
    }

    // encode string
    str_encode(buffer, string, length);
}

int generate_key(char *buffer, const char *word, const char *salt, const unsigned int length, const unsigned int algorithm, const unsigned int extended)
{
    // Version check should be the very first call because it
    // makes sure that important subsystems are intialized.
    if (!gcry_check_version (GCRYPT_VERSION))
    {
        fputs ("libgcrypt version mismatch\n", stderr);
        return 2;
    }

    if (extended) {
        alphabet = baseE91;
    } else {
        alphabet = base64;
    }

    // process input
    unsigned int input_length = strlen(word) + strlen(salt);

    // prepare hash buffer
    unsigned int hash_size = gcry_md_get_algo_dlen( algorithm ) * sizeof (unsigned char);
    char* hash = calloc( gcry_md_get_algo_dlen( algorithm ), sizeof (unsigned char));

    if (hash == NULL || mlock(hash, hash_size))
    {
        fputs ("could not allocate space for hash computation\n", stderr);
        return 3;
    }

    snprintf(hash, (input_length + 1) * sizeof (char), "%s%s", word, salt);

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

    //zip_encode(buffer, hash, hash_size, length);
    if (length > hash_size) {
        str_encode(buffer, hash, hash_size);
    }
    else {
        str_encode(buffer, hash, length);
    }

    memset(hash, 0, hash_size);

    free(hash);
    munlock(hash, hash_size);

    // TODO do we have to do anything with the secure memory after this?

    return (length - strlen (buffer));
}
