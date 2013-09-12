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

The tests can be compiled with

```
./install test
```

Requirements
============

- a c compiler (gcc for the install script)
- gtk3
- libgcrypt
- cunit for testing

Usage
=====

```
psafe returns a password for any given profile and password.
profile should be an easy to remember name for your password, can be provided later.
usage: psafe [OPTIONS] [profile]
    -a, --algorithm   set hash algorithm, see readme for available options
    -c, --license     show license notice
    -e, --extended     use extended alphabet
    -h, --help        show this help message
    -l, --key-size    set key length to N, default is 12
    -p, --password    set password to x (only for testing purposes!)
    --print-key       print the key to stdout
    -r, --repetitions set number of repetitions; default is 20000
```

A typical call would look like this:   

```psafe my_profile_name```   

This call would ask the user for a password and save the result to the primary X
selection and clipboard for 10 seconds. The same profile, password and key length will always result in the same key.

Key Algorithm
=============

Version 1.* uses libgcrypts whirlpool as standard algorithm. Currently profile and password
will be concatenated and encrypted 
```whirlpool(profile . password)```
Other available algorithms are: tiger, tiger1, tiger2, sha256, sha512   

#### Issues

* repetetive profile & password combinations result in the same output: 
  ```AAA+p = AAAA+p != AAAAA+p = AAAAAAA+p```   
  For key size 12.   
  This makes sense: 12/3=4, 12/4=3, 12/5=2.4, 12/7=1.71..
  Therefore: The current key algorithm is s**t <3


Todo
====

- find a suitable name which is not used yet   
- key algorithm    
- windows and osx compatibility
- qt version
- config file and wizard?
- variable clipboard timeout
- file reading and handling
- more input strings

Changelog
=========

##### v1.1.3
- password characters now chosen from hardcoded alphabet, extended characters
  implemented with -e   

##### v1.1.2
- algorithm is now variable
- variable hash repetitions

##### v1.1.1
- started efforts to increase key security    
  http://stackoverflow.com/questions/348109/is-double-hashing-a-password-less-secure-than-just-hashing-it-once   
  currently the hash algorithm gets repeated

##### v1.1
- removed literal and array operations source

##### v1.0   
- switched key algorithm to whirlpool hash function from libgcrypt
- fixed trailing newline bug in console input
- tried to implement buffer overflow protection for user input

##### v0.9   
- gui input working
- cleaned up a a lot of code
- fixed a bug where literal subtraction could result in negative values

##### v0.8   
- key algorithm needs rethinking, every change in key generation should change
  second version digit for easy version control, current version has some major
  issues
- linux flow is working fine (calls through terminal and pipe are working)   

----

*Copyright (C) 2013 Aljosha Friemann*

*This program is free software: you can redistribute it and/or modify*
*it under the terms of the GNU General Public License as published by*
*the Free Software Foundation, either version 3 of the License, or*
*(at your option) any later version.*

*This program is distributed in the hope that it will be useful,*
*but WITHOUT ANY WARRANTY; without even the implied warranty of*
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the*
*GNU General Public License for more details.*

*You should have received a copy of the GNU General Public License*
*along with this program.  If not, see http://www.gnu.org/licenses/*
