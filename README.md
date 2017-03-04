RSHELL
==========

Licensing Information: READ LICENSE
---
Project source can be downloaded from https://github.com/jzena001/rshell.git
----

Author & Contributor List
-----------
Matthew LeBouvier

Joshua Zenarosa

All other known bugs and fixes can be sent to jzena001@ucr.edu

Reported bugs/fixes will be submitted to correction.

File List
---------
```
.:

Makefile

LICENSE

README.md

hw2.txt

./src

./tests
```
```
/src:

main.cpp

```
```
./tests:

single_command.sh

multi_command.sh

commented_command.sh

exit.sh
```

Once you have cloned the directory to your local machine, follow the directions below:
--------------------------------------------------------------------------------------
1. `cd` into `rshell` directory

2. Call `make`

3. `cd` into `bin`

4. Call `rshell` executable file

RShell will now open up instead of BASH and you can execute all commands included in usr/bin.

Program reviewed by the University of California, Riverside.
------------------------------------------------------------
Basic Overview of Command Shells: [HERE](http://linuxgazette.net/111/ramankutty.html)

This program is developed to write a simple command shell called "RShell."

- It will offer similarities such as the normal BASH Command shell.

- Can call all commands of BASH in usr/bin

- Can call on multiple commands using connectors "&&" "||" and ";" 

- Have special built in command "exit" to exit RSHELL and return to your local SHELL

Bugs
---
1. Program has errors when a space is entered after a command and before a connector or a comment. 
