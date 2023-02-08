# How To Run:

## Install flex and yacc

Ubuntu / Debian:
```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install flex bison
```

Arch
```
sudo pacman -Syu flex bison
```

Fedora / RHEL
```
dnf install flex-devel bison-devel
```

## Running lexical analyzer using LEX
```l
ex lexi.l
gcc lex.yy.c
```

## Running programs with LEX and YACC
```
lex *.l
yacc -d *.y
gcc *.c -w
```
