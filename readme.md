CPH - C Password Hasher
=======================

CPH computes passwords from given strings and prints them to stdout or writes them to
the clipboard for a specefied amount of time.   

Installation
============

Use cmake to create a Makefile and compile as usual with make.
An option to compile without X/GTK will eventually be added.

Requirements
============

- a c compiler
- cmake/make
- gtk3
- libgcrypt

Usage
=====

```
cph returns a password for any given profile and password.\n
profile should be an easy to remember name for your password, can be provided later.\n
usage: cph [OPTIONS]
    -h, --help         show this help message
    -c, --license      show license notice
    -v, --version      show version
    -a, --algorithm X  set hash algorithm, see readme for available options
    -e, --extended     use extended alphabet
    -g, --with-gui     use gui input
    -l, --length N     set password length, default is 12

input switches:
    -w, --word W
    -s, --salt S
```

The same word, salt and key length will always result in the same key.

Key Algorithm
=============

Version 1.* uses libgcrypts whirlpool as standard algorithm. Currently profile and password
will be concatenated and hased 
```sha512(word + salt)```
Other available algorithms are: tiger, tiger1, tiger2, sha256, whirlpool   
The included analysis scripts are rather useless. However, if you would simply like to see what calculated keys typically look like,
they should provide a reasonable starting point.

#### Issues

- hash without random seed might be too insecure, a piece of static personal information could be saved and used (e.g. birthdate)
- key length input is not used

Todo
====

- windows and osx compatibility
- qt version
- enhance key algorithm?
- config file and wizard?
- variable clipboard timeout
- more input strings?

Similar Projects
================

- The wonderful [PwdHash](https://www.pwdhash.com/) used in several browser
  plugins

Changelog
=========

##### v1.4.1
- removed clipboard handling from command line to make way for X free version
- moved argument parsing to seperate file to clean up main file
- included cmake configuration

##### v1.3.1
- changed name to cph - c password hasher; for this is what it does

##### v1.3
- fixed major bug that would cause gui input to create random passwords

##### v1.2
- password characters now chosen from hardcoded alphabet, extended characters
  implemented with -e   

##### v1.1.2
- algorithm is now variable
- variable hash repetitions

##### v1.1.1
- started efforts to increase key security    
  [related stackoverflow post](http://stackoverflow.com/questions/348109/is-double-hashing-a-password-less-secure-than-just-hashing-it-once)   
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
