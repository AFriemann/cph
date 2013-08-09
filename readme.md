PSAFE - working title
=====================

psafe calculates passwords from given strings and prints them or writes them to
the clipboard for a specefied amount of time.   

Installation
============

To install psafe, simply run the install script like so:   

```
./install   
```

The tests cann be compiled with

```
./install test
```

Usage
=====

```
usage: psafe [OPTION] [profile] [key size]
          -c, --config: run configuration wizard
          -f, --file: provide non-standard config file
          -h, --help: show this help message
          --print-key: print key instead of writing it to the clipboard
          --stored-pass: load password from file (TODO)
```

A typical call would look like this:   

```psafe --print-key my_profile_name 12```   

This call would ask the user for a password and print it out on console. The
same profile, password and key length will always result in the same key.   

Todo
====

- clipboard (only --print-key working yet) [done with python wrapper -> pysafe.py]
- clipboard deletion [done! pysafe.py : FUCK ICCCM!] 
- better key algorithm
- config wizard
- file reading and handling
- more input strings (increase entropy)
- windows compatibility (maybe use pyperclip for wrapper)
- not-in-shell mode for password
