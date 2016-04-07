#include <iostream>

using namespace std;

enum Color {
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    purple = 35,
    cyan = 36,
    white = 37
};

class Term {
    public:
        void clearScreen();
        void setCursorPos(int row, int column);
        void setForegroundColor(Color color);
        void setBackgroundColor(Color color);
};