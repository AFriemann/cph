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

Usage
=====

```
psafe returns a password for any given profile and password.
profile should be an easy to remember name for your password, the key size is optional; the current default is 12.
	usage: psafe <profile> [key size]
	-h, --help: show this help message
```

A typical call would look like this:   

```psafe my_profile_name 12```   

This call would ask the user for a password and print it out on console. The
same profile, password and key length will always result in the same key.   
Please use the included python wrapper, since a call to psafe simply outputs the
key to stdout:   

```pysafe my_profile_name 12```

will do the same as the call above but will pipe the key to your primary X
selection and remove it after 10 seconds.


Key Algorithm
=============

Currently the profile name and password get converted to int arrays like so:

```
profile=foobar, keySize=5   

foobar -> 102,111,111,98,97,114 -> [102+114,111,111,98,97] -> [216,111,111,98,97]
```

The results then gets warped by multiplicating each element with its index
```[216*1,111*2,111*3,98*4,97*5] -> [216,222,333,392,485]```

And the reverse:
```[216*5,222*4,333*3,392*2,485*1] ->  [1080,888,999,784,485]```

And a centre shift:
```[1080,888+784,999+(888*784),784-888,485] -> [1080,1672,697191,-104,485]```
All arithmetic operations are calculated modulo 126 with a minimum value of 33, so the
resulting array would be
```[72,34,33,55,107]```
The two calculated arrays will then be multiplicated and added, so with a
hypothetical (but nonsensical) password result ```[1,1,1,1,1]``` the end result would be:
```[73,35,34,56,108] -> I#"8l```   


Todo
====

- repetetive profile & password combinations result in the same output: AAA+BBB = AAAA+BBB etc.
- better key algorithm (bits & bytes ftw!)   
  -> injective or bijective function for encryption.   
  -> encrypt the profile name with password? RSA?   
- windows compatibility (maybe use pyperclip for wrapper)
- not-in-shell mode for password   
- variable clipboard timeout    
---- bullshit
- config wizard
- file reading and handling
- more input strings 

*Copyright (C) 2013 Aljosha Friemann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see [http://www.gnu.org/licenses/].*
