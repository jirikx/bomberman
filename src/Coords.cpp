#include "Coords.hpp"

Coords::Coords(int x, int y)
  : x(x), y(y) {}

bool Coords::operator<(const Coords &rhs) const {
    if (x == rhs.x)
        return y < rhs.y;
    
    return x < rhs.x;
}

bool Coords::operator==(const Coords &rhs) const {
    return x == rhs.x && y == rhs.y;
}

Coords Coords::operator+(const Coords &rhs) const {
    return {x + rhs.x, y + rhs.y};
}

Coords Coords::operator-(const Coords &rhs) const {
    return {x - rhs.x, y - rhs.y};
}

Coords operator+(Coords coords, EAction action) {
    switch (action) {
        case EAction::MOVE_UP:
            coords.y -= 1;
            break;
        case EAction::MOVE_DOWN:
            coords.y += 1;
            break;
        case EAction::MOVE_LEFT:
            coords.x -= 1;
            break;
        case EAction::MOVE_RIGHT:
            coords.x += 1;
            break;
        default:
            break;
    }

    return coords;
}