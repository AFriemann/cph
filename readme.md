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
- cunit for testing

Usage
=====

```
psafe returns a password for any given profile and password.
profile should be an easy to remember name for your password, can be provided later.
usage: psafe [OPTIONS] [profile]
	-h, --help: show this help message
	-l, --key-size=[N]: set key length to N, default is 12
	-p, --password=[x]: set password to x (only for testing purposes!)
	-c, --license: show license notice
```

A typical call would look like this:   

```psafe my_profile_name```   

This call would ask the user for a password and save the result to the primary X
selection and clipboard for 10 seconds. The same profile, password and key length will always result in the same key.

Key Algorithm
=============

Version 1.* uses libgcrypts whirlpool algorithm. Currently profile and password
will be concatenated and encrypted 
```whirlpool(profile . password)```

#### Issues

* repetetive profile & password combinations result in the same output: 
  ```AAA+p = AAAA+p != AAAAA+p = AAAAAAA+p```   
  For key size 12.   
  This makes sense: 12/3=4, 12/4=3, 12/5=2.4, 12/7=1.71..
  Therefore: The current key algorithm is s**t <3


Todo
====

- find a suitable name which is not used yet   
- better key algorithm (bits & bytes ftw!)    
  -> p_i = p_i + |p|*i in string to int array conversion would fix the
  repetetive key problem   
  -> injective or bijective function for encryption.   
  -> encrypt the profile name with password? RSA?   
- windows and osx compatibility
- specify alphabet (many services don't accept special characters)   
- qt version
- config file and wizard
- variable clipboard timeout
- file reading and handling
- more input strings

Changelog
=========

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
