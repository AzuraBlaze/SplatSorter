#include "Team.hpp"

int Team::rating() const
{
    int result = 0;

    for(const auto& player : players_m)
        result += player.rating();
    
    return result;
}