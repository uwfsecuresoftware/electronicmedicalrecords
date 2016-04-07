#include "term.h"

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