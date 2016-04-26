CPH - C Password Hasher
=======================

CPH computes passwords from given strings and prints them to stdout or writes them to
the clipboard for a specefied amount of time.   

Installation
============

> ./configure [--enable-gtk]  
> make && make install

An ebuild is available in my repository at

https://bitbucket.org/afriemann/gentoo

Simply add the file `/etc/portage/repos.conf/afriemann.conf`

```
[afriemann]
location = /usr/local/portage/afriemann
sync-type = git
sync-uri = https://bitbucket.org/afriemann/gentoo.git
auto-sync = yes
```

and run emerge --sync afriemann

Requirements
============

- a c compiler
- cmake/make
- libgcrypt

Optional: 
  
- gtk3

Usage
=====

> cph returns a hash for any given word and salt.   
> usage: cph [OPTIONS]   
>     -h, --help         show this help message   
>     -c, --license      show license notice   
>     -v, --version      show version   
>     -a, --algorithm X  set hash algorithm, see readme for available options   
>     -e, --extended     use baseE91 instead of base64   
>     -l, --length N     set password length, default is 12   
>   
> input switches:   
>     -w, --word W   
>     -s, --salt S   

The same word, salt and key length will always result in the same key.

Exit codes are defined as follows:

> define EXIT_OK 0   
> define EXIT_MEM_ERR 1   
> define EXIT_INPUT_ERR 2   
> define EXIT_LIBGRCYPT_ERR 3   
> define EXIT_KEY_ERROR 4   

Key Algorithm
=============

Version 1.* uses libgcrypts sha512 as standard algorithm. Currently profile and password
will be concatenated and hashed 
```sha512(word + salt)```
Other available algorithms are: tiger, tiger1, tiger2, sha256, whirlpool   

#### Issues

- hash without random seed might be too insecure, a piece of static personal information could be saved and used (e.g. birthdate)
- long inputs result in core dumps (with or without GTK). Current fix is to "only" allow inputs with length <= 32 characters.

Todo
====

- **manually closing one of the windows should terminate the entire program**
- manpage
- windows and osx compatibility
- qt version
- enhance key algorithm?
- variable clipboard timeout
- more input strings?
- config file and wizard?
- copying to selection might leak passwords

Similar Projects
================

- [PwdHash](https://www.pwdhash.com/) used in several browser plugins

Changelog
=========

##### v1.5.5
- moved buffer initialization functions to cph_memory files

##### v1.5.4
- using stdbool instead of defines for boolean values

##### v1.5.3
- added NULL pointer checks
- added return value logic to some methods
  - inputs exceeding INPUT_MAX will now result in termination
  - cph exit codes should contain a bit more information (see readme)

##### v1.5.2
- reduced input cap from 64 characters to 32. exceeding characters will be discarded (this will change in the future)

##### v1.5.1
- can now be compiled with or without gtk support
- removed getpass usage (manually disabling output now)
- changed extended alphabet to baseE91 and default to base64

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
