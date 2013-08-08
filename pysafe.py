#!/usr/bin/python

from subprocess import Popen, PIPE
import sys
import os
import time

def text_to_clipboard(text):
    Popen(['xsel', '-pi'], stdin=PIPE).communicate(text)

def clear_clipboard():
    Popen(['xsel', '-d'])

PSAFE_ARGS = ['-l'] + sys.argv[1::2] # ignore first argument (namely pysafe)
PSAFE_CALL = ['./psafe'] + PSAFE_ARGS # regular psafe call syntax! yay!

# run psafe and save output
PROCESS = Popen(PSAFE_CALL, shell=False, stdout=PIPE,
    stderr=PIPE)

OUT, ERR = PROCESS.communicate()

# if stderr not empty, exit and print errors
if not ERR:
    text_to_clipboard(OUT)
else:
    print(ERR)
    sys.exit(1)

# now fork and sleep!
if os.fork():
    sys.exit()

time.sleep(10)

clear_clipboard()

sys.exit(0)
