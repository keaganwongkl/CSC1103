# CSC1103 Mini Project - Tic-tac-toe game
## By: Bryant Chendra, Dallon Au, Gabriel Lau, Keagan Wong, Poh Kuang Yi

This is a simple Tic-tac-toe game built by 5 SIT Computing Science students. This game is written with C with GTK UI libraries. The game is compatible with both Mac and Windows machines.

## Installation of dependencies for Windows
```
BLANK
```

## Installation of dependencies for Mac
Installation of Homebrew package manager to install GTK and pkg-config
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
Installation of GTK
```
brew install gtk
```
Installation of pkg-config
```
brew install pkg-config
```
With all the dependencies installed, you can now compile the game with the command
```
gcc $(pkg-config --cflags gtk4) -o main main.c $(pkg-config --libs gtk4)
```