#pragma once

#include "global.hpp"

enum class Color {
    DEFAULT,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    WHITE
};

void setColor(Color color);

inline Color getColor(const std::string& colorStr) {
    std::string color = colorStr;
    std::transform(color.begin(), color.end(), color.begin(), ::tolower);

    if (color == "red") {
        return Color::RED;
    } else if (color == "green") {
        return Color::GREEN;
    } else if (color == "blue") {
        return Color::BLUE;
    } else if (color == "yellow") {
        return Color::YELLOW;
    } else if (color == "cyan") {
        return Color::CYAN;
    } else if (color == "magenta") {
        return Color::MAGENTA;
    } else if (color == "white") {
        return Color::WHITE;
    } else {
        return Color::DEFAULT;
    }
}

template<typename T>
void Print(T arg) {
    std::cout << arg;
}

// Recursive template function to print multiple arguments
template<typename T, typename... Args>
void Print(T firstArg, Args... args) {
    if constexpr (std::is_same_v<T, Color>) {
        setColor(firstArg);
        Print(args...);
        setColor(Color::DEFAULT); // Reset color to default after printing
    } else {
        std::cout << firstArg << " ";
        Print(args...);
    }
}