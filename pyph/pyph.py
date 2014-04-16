#!/bin/env python

LICENSE= """PyPh  Copyright (C) 2013  Aljosha Friemann

This program comes with ABSOLUTELY NO WARRANTY!
This is free software, and you are welcome to redistribute it
under certain conditions; please read the provided license file for details."""

import logging

from sys import exit
from getpass import getpass
from argparse import ArgumentParser,Action,SUPPRESS

#from Crypto.Cipher import AES
#import crypt as CRYPT_LIB
#import hmac as CRYPT_LIB
import hashlib as CRYPT_LIB


DEFAULT_LENGTH  = 18
DEFAULT_ALGO    = 'md5'

ABC_EXT =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+/$-_|&%*=:!#~@><.,^"
ABC     =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

ALGORITHMS = CRYPT_LIB.algorithms

LOG_FORMAT = '%(asctime)-15s %(message)s'

class license(Action):
    def __call__(self, parser, namespace, values, option_string=None):
        print(LICENSE)
        exit(0)

parser = ArgumentParser(
    prog='pyph',
    description='Python Password Hasher',
    usage='%(prog)s [options]')

parser.add_argument(
    '--print-key',
    action='store_true',
    help='print password')

parser.add_argument(
    '--license',
    nargs=0,
    action=license,
    help='print license')

parser.add_argument(
    '--version',
    action='version',
    version='%(prog)s 0.1')

parser.add_argument(
    '-a', '--algorithm',
    choices=ALGORITHMS,
    default=DEFAULT_ALGO,
    help='define algorithm')

parser.add_argument(
    '-e', '--extended',
    action='store_true',
    help='use extended alphabet')

parser.add_argument(
    '-l','--length',
    default=DEFAULT_LENGTH,
    metavar='L',
    type=int,
    help='specify password length (default '+str(DEFAULT_LENGTH)+')')

parser.add_argument(
    '-w','--word',
    help='word to be hashed')

parser.add_argument(
    '-s','--salt',
    help='salt to be used in hash function')

def encrypt(word, salt, length, algorithm, alphabet):
    hash_func = getattr(CRYPT_LIB,algorithm)()
    hash_func.update(word.encode('utf-8') + salt.encode('utf-8'))

    # is this at least remotely reasonable?
    # TODO: what happens if length > len(digest)?
    return reduce(lambda s, c: s + alphabet[(ord(c) % len(alphabet)) - 1], hash_func.digest(),"")[:length].strip()

def main(args,log):
    try:
        cipher = encrypt(
                args.word or getpass('word: '),
                args.salt or getpass('salt: '),
                args.length,
                args.algorithm,
                (args.extended and ABC_EXT) or ABC)

        if cipher is not None:
            print(cipher)
        else:
            raise Exception("Cipher was None")
    except:
        log.exception("[ERROR]")
        exit(1)
    finally:
        cipher = "" # does this make sense at all?

    exit(0)

if __name__ == '__main__':
    args = parser.parse_args()

    logging.basicConfig(format=LOG_FORMAT)

    main(args,logging.getLogger('logger'))
