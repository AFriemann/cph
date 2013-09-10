/*
psafe key algorithm source, generates keys.
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


#include "psafeKey.h"

char 
literal(const char c) {
  char result = c % LITERAL_MAX;

  if (result < 0)
    result += LITERAL_MAX;
  if (result < LITERAL_MIN)
    result += LITERAL_MIN;

  return result;
}


void 
generate_key(char *buffer, const char *profile, const char *password, const int key_size, const unsigned int algorithm, const int reps) {
  // Version check should be the very first call because it
  // makes sure that important subsystems are intialized.
  if (!gcry_check_version (GCRYPT_VERSION))
    {
      fputs ("libgcrypt version mismatch\n", stderr);
      exit (2);
    }

  // process input
  int input_length = ( strlen (profile) ) + ( strlen (password) );
  //char *input = malloc(input_length * sizeof (char));

  // prepare hash buffer
  int hash_length = gcry_md_get_algo_dlen( algorithm );
  char* hash = malloc( hash_length * sizeof (char) );

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

  int ind = 0;

  /* calculate hash and write to hash buffer */
  while (ind++ < reps)
    gcry_md_hash_buffer( algorithm, hash, hash, input_length );

  int i;
  for ( i = 0; i < key_size; i++) {
    snprintf( buffer++, 3, "%c", literal( hash[i] ) );
  }

  memset(hash, 0, hash_length * sizeof (unsigned char));
  //memset(input, 0, input_length * sizeof (char));

  free(hash);
  //free(input);
}
