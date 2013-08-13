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

Key Algorithm
=============

Currently the profile name and password get converted to int arrays like so:   

```
profile=foobar, keySize=5   

foobar -> 102,111,111,98,97,114 -> [102+114,111,111,98,97]
```

The results get then warped by multiplicating each element with its index   
```[216,111,111,98,97]-> [216*1,111*2,111*3,98*4,97*5] -> [216,222,333,392,485]```

And the reverse:   
```[216,222,333,392,485] -> [216*5,222*4,333*3,392*2,485*1] ->  [1080,888,999,784,485]```

And a centre shift:
```[1080,888,999,784,485] -> [1080,888+784,999+(888*784),784-888,485] -> [1080,1672,697191,-104,485]```
All arithmetic operations modulo 126 with a minimum value of 33, so the
resulting array would be   
```[72,34,33,55,107]```
The two calculated arrays will then be multiplicated and added, so with a
hypothetical password result ```[1,1,1,1,1]``` the end result would be:   
```[73,35,34,56,108] -> I#"8l```   


Todo
====

- better key algorithm (bits & bytes ftw!)
- windows compatibility (maybe use pyperclip for wrapper)
- not-in-shell mode for password   
---- bullshit
- config wizard
- file reading and handling
- more input strings 

