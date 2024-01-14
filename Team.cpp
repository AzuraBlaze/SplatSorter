#include "Team.hpp"

int Team::rating() const
{
    int total_rating = 0;

    for(const auto& player : players_m)
        total_rating += player.rating();
    
    return total_rating;
}


void Team::add_player(const Player& player)
{
    players_m.insert(player);
}


Team::iterator Team::begin()
{
    return players_m.begin();
}

Team::iterator Team::end()
{
    return players_m.end();
}