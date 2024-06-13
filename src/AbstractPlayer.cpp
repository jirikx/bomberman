#include "AbstractPlayer.hpp"

AbstractPlayer::AbstractPlayer(int hp, int bombs, Coords coords)
  : m_Stats(hp, bombs, 0, false, 0), m_Score(0), m_Coords(coords),
    m_Texture(' '), m_ParticipatesInLeaderboard(false) {}

AbstractPlayer::AbstractPlayer(const PlayerStats &stats, const Coords &coords, char texture, const std::string &nickname)
  : m_Stats(stats), m_Score(0), m_Coords(coords), m_Texture(texture), m_NickName(nickname), m_ParticipatesInLeaderboard(false) {}

AbstractPlayer::~AbstractPlayer() = default;

bool AbstractPlayer::getHit(int damage) {
    m_Stats.hp -= damage;
    return m_Stats.hp == 0;
}

bool AbstractPlayer::isAlive() const {
    return m_Stats.hp > 0;
}

bool AbstractPlayer::isImmuneAgainst(const std::shared_ptr<AbstractPlayer> &player) const {
    return m_Stats.hasImmunity && m_Id == player->m_Id;
}

bool AbstractPlayer::participatesInLeaderboard() const {
    return m_ParticipatesInLeaderboard;
}

bool CompareById::operator()(const std::shared_ptr<AbstractPlayer> &lhs, const std::shared_ptr<AbstractPlayer> &rhs) const {
    return lhs->m_Id < rhs->m_Id;
}
