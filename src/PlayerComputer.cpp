#include "PlayerComputer.hpp"

PlayerComputer::PlayerComputer(int hp, int bombs, const Coords &coords, const std::shared_ptr<AbstractPlayer> &enemy)
    : AbstractPlayer(hp, bombs, coords), m_Enemy(enemy) {
    m_Texture = 'B';
    m_NickName = "Robot";
}

EAction PlayerComputer::updateAction() {
    Coords direction = m_Coords - m_Enemy->m_Coords;
    if (direction == Coords(0, 0))
        return EAction::DO_NOTHING;

    if (direction.x > 0)
        return EAction::MOVE_LEFT;
    else if (direction.x < 0)
        return EAction::MOVE_RIGHT;
    else if (direction.y > 0)
        return EAction::MOVE_UP;
    else if (direction.y < 0)
        return EAction::MOVE_DOWN;

    return EAction::MOVE_UP;
}