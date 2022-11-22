# CSC1103 Mini Project - Tic-tac-toe game
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
If you are using gtk3, you have to uninstall gtk3 and install gtk4 instead. To do so please follow the instructions below.
```
brew remove gtk3
brew install gtk4
```