PSAFE - working title
=====================

psafe calculates passwords from given strings and prints them or writes them to
the clipboard for a specefied amount of time.   

```
usage: psafe [OPTION] [profile] [key size]
          -c, --config: run configuration wizard
          -h, --help: show this help message
          -p, --print: print key instead of writing it to the clipboard"
```

A typical call would look like this:   

```psafe my_profile_name 12```   

This call would ask the user for a password and print it out on console. The
same profile, password and key length will always result in the same key.   
