#include "Roster.hpp"

using namespace std;
using namespace SugarPP;


size_t Roster::size() const
{
    return players_m.size();
}

size_t Roster::length() const
{
    return size(); 
}

bool Roster::empty() const
{
    return (size() == 0);
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


Roster::iterator Roster::begin()
{
    return players_m.begin();
}

Roster::iterator Roster::end()
{
    return players_m.end();
}

Roster::iterator Roster::search(const string& player_name)
{
    for(size_t i = 0; i < players_m.size(); i++)
        if(players_m[i].name() == player_name)
            return players_m.begin() + i;
    
    return players_m.end();
}