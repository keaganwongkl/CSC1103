# Directions for Mac OS X
## WARNING
### Please use GTK 4
If you are using gtk3, you have to uninstall gtk3 and install gtk4 instead. To do so please follow the instructions below.
```
brew remove gtk+3
brew install gtk4
```
### If you're using an Intel Mac
The current version of the game is compiled on an ARM Mac. If you are running an Intel Mac you may need to recompile the game.
## Installation of dependencies for Mac
THis is a guide on how to install the GTK UI library for Mac. This is required to compile the and run the game.
### Install Homebrew
Installation of Homebrew package manager to install GTK and pkg-config
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
### Install GTK and pkg-config
Using the Homebrew package manager, install GTK and pkg-config
```
brew install gtk
```
Installation of pkg-config
```
brew install pkg-config
```
### Compile and run the game
With all the dependencies installed, you can now compile the game with the command
```
gcc $(pkg-config --cflags gtk4) -o main main.c $(pkg-config --libs gtk4)
```