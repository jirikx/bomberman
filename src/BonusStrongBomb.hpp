#pragma once
#include "Bonus.hpp"

/**
 * @brief Makes the explosion perimeter greater than it was before
 *
 * If the application of the bonus lowered the explosion perimeter
 * of the bomb, the bonus wouldn't apply.
 *
 */
class BonusStrongBomb : public Bonus {
public:
    explicit BonusStrongBomb(int explosionPerimeter = 4);

    void activateBonus(PlayerStats &playerStats) override;

private:
    int m_ExplosionPerimeter;
};