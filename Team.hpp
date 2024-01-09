#ifndef SPLATSORTER_TEAM_HPP
#define SPLATSORTER_TEAM_HPP

#include "Player.hpp"
#include <unordered_set>

class Team
{
    std::unordered_set<Player> players_m;

    public:

    Team()
    : players_m() {}


    int rating() const;
};

#endif /* SPLATSORTER_TEAM_HPP */