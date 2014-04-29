#!/bin/env python

LICENSE= """PyPh  Copyright (C) 2013  Aljosha Friemann

This program comes with ABSOLUTELY NO WARRANTY!
This is free software, and you are welcome to redistribute it
under certain conditions; please read the provided license file for details."""

import logging

from sys import exit
from getpass import getpass
from argparse import ArgumentParser,Action,SUPPRESS

# python 2 vs. 3
try: import Tkinter as tk
except: import tkinter as tk

### Crypto library import
#
#from Crypto.Cipher import AES
#import crypt as CRYPT_LIB
#import hmac as CRYPT_LIB
import hashlib as CRYPT_LIB

### defaults

DEFAULT_LENGTH  = 18
DEFAULT_ALGO    = 'md5'

ABC_EXT =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+/$-_|&%*=:!#~@><.,^"
ABC     =  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

# if there is only one, set to [algo]
ALGORITHMS = CRYPT_LIB.algorithms

LOG_FORMAT = '\n%(asctime)-15s %(message)s'

### argpasrse configuration

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
    '--selection',
    choices=['primary', 'secondary'],
    #default='primary',
    help='store password in given selection')

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
    '--gui',
    action='store_true',
    help='use with gui')

parser.add_argument(
    '-t', '--timeout',
    default=5.0,
    type=float,
    metavar='t',
    help='set timeout for input')

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

### pyph

class GUI(tk.Tk):
    __WIDTH  = 120
    __HEIGHT = 1
    def __init__(self, prompt, timeout):
        tk.Tk.__init__(self)

        # set basics
        self.title('pyph')
        self.wm_client('pyph')
        self.wm_maxsize(width=self.__WIDTH, height=self.__HEIGHT)
        self.wm_minsize(width=self.__WIDTH, height=self.__HEIGHT)
        self["padx"] = 2
        self["pady"] = 2

        self.label = tk.Label(self, text=prompt)
        self.label.pack(side=tk.TOP)

        self.entry = tk.Entry(self, width=self.__WIDTH, show='*')
        self.entry.bind('<Return>', self.callback)
        self.entry.pack(side=tk.BOTTOM)

        # self destruct
        self.after(int(timeout * 1000), self.destruct)

        self.entry.focus_set()
        self.bell()

        self.mainloop()

    def get_content(self):
        try:
            return self.content
        except AttributeError:
            raise Exception('window closed before entry finished')

    def callback(self, event):
        self.content = self.entry.get()
        self.destruct()

    def destruct(self):
        self.data = None
        self.destroy()

def gui_input(prompt, timeout):
    return GUI(prompt, timeout).get_content()

def cli_input(prompt, timeout):
    # TODO: timeout
    return getpass(prompt)

def get_input(prompt, gui, timeout):
    if gui:
        return gui_input(prompt, timeout)
    else:
        return cli_input(prompt, timeout)

def encrypt(word, salt, length, algorithm, alphabet):
    hash_func = getattr(CRYPT_LIB,algorithm)()
    hash_func.update(word.encode('utf-8') + salt.encode('utf-8'))

    # is this at least remotely reasonable?
    # TODO: what happens if length > len(digest)?
    return reduce(lambda s, c: s + alphabet[(ord(c) % len(alphabet)) - 1], hash_func.digest(),"")[:length].strip()

def main(args, log):
    try:
        cipher = encrypt(
                args.word or get_input('word: ', args.gui, args.timeout),
                args.salt or get_input('salt: ', args.gui, args.timeout),
                args.length,
                args.algorithm,
                (args.extended and ABC_EXT) or ABC)

        if cipher is None:
            raise Exception("Cipher was None")

        if args.print_key:
            print(cipher)

        if args.selection is not None:
            # TODO: clipboard
            pass

    except:
        log.exception("")
        exit(1)

    exit(0)

if __name__ == '__main__':
    args = parser.parse_args()
    logging.basicConfig(format=LOG_FORMAT, level=0)

    main(args, logging.getLogger('logger'))
