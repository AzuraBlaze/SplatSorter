#ifndef SPLATSORTER_TEAM_HPP
#define SPLATSORTER_TEAM_HPP

#include <unordered_set>

#include "Common.hpp"
#include "Player.hpp"

class Team
{
    std::unordered_set<Player> players_m;

    public:

    using iterator = std::unordered_set<Player>::iterator;

    int rating() const;

    void add_player(const Player& player);

    iterator begin();
    iterator end();
};

#endif /* SPLATSORTER_TEAM_HPP */