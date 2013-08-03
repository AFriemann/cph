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

- clipboard (only --print-key working yet)
- clipboard deletion
  -> http://www.jwz.org/doc/x-cut-and-paste.html
  -> http://tronche.com/gui/x/xlib/
- better key algorithm
- config wizard
- file reading and handling
- more input strings
