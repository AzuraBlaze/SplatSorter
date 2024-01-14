#ifndef SPLATSORTER_ROSTER_HPP
#define SPLATSORTER_ROSTER_HPP

#include <vector>
#include <initializer_list>
#include <string>

#include "Common.hpp"
#include "Player.hpp"

class Roster
{
    public:

    using iterator = std::vector<Player>::iterator;

    private:

    std::vector<Player> players_m;

    public:

    Roster(std::initializer_list<Player> players)
    : players_m(players.begin(), players.end()) {}
    

    iterator search(const std::string& player_name);

    bool contains(const std::string& player_name) const;

    Roster& add_player(const Player& player);
    Roster& add_player(const std::string& name, int wins, int losses);
};

#endif /* SPLATSORTER_ROSTER_HPP */