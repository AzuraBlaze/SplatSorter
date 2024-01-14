#include "Roster.hpp"

using namespace std;
using namespace SugarPP;

Roster::iterator Roster::search(const string& player_name)
{
    for(size_t i = 0; i < players_m.size(); i++)
        if(players_m[i].name() == player_name)
            return players_m.begin() + i;
    
    return players_m.end();
}

bool Roster::contains(const string& player_name) const
{
    for(const Player& player : players_m)
        if(player.name() == player_name)
            return true;
    
    return false;
}


Roster& Roster::add_player(const Player& player)
{
    iterator it = search(player.name());

    if(it == players_m.end())
        players_m.push_back(player);
    else
        *it = player;
    
    return *this;
}

Roster& Roster::add_player(const string& name, int wins, int losses)
{
    return add_player(Player(name, wins, losses));
}