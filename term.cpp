#include "headers/term.h"

void Term::clearScreen() {
    std::cout << "\033[2J";
}

void Term::setCursorPos(int row, int column) {
    std::cout << "\033[" << row << ";" << column << "H";
}

void Term::setForegroundColor(Color color) {
    std::cout << "\033[" << color << "m";
}

void Term::setBackgroundColor(Color color) {
    std::cout << "\033[" << (color + 10) << "m";
}

int * Term::getTerminalSize() {
    struct winsize w;
    
    ioctl(0, TIOCGWINSZ, &w);
    
    return new int[2] {w.ws_row, w.ws_col};
}

int Term::getTerminalRows() {
    int * size = getTerminalSize();
    return size[0];
}

int Term::getTerminalColumns() {
    int * size = getTerminalSize();
    return size[1];
}