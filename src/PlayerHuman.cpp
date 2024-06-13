#include "PlayerHuman.hpp"

PlayerHuman::PlayerHuman(const PlayerStats &stats, const Coords &coords, char texture, std::string &nickname,
                         const std::map<int, EAction> &controls)
  : AbstractPlayer(stats, coords, texture, nickname), m_Controls(controls) {
    m_ParticipatesInLeaderboard = true;
}

PlayerHuman::PlayerHuman(int hp, int bombs, const std::string &nickname, Coords coords, const std::map<int, EAction> &controls)
  : AbstractPlayer(hp, bombs, coords), m_Controls(controls) {
    m_ParticipatesInLeaderboard = true;
    m_Texture = 'o';
    m_NickName = nickname;
}

EAction PlayerHuman::updateAction() {
    return m_GameBoard->getAction(m_Controls);
}