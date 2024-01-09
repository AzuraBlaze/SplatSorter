#include <iostream>
#include "Player.hpp"

#include <unordered_set>
#include <vector>

int main()
{
    std::vector<Player> player_vec = 
    {
        { "John", 3, 4 },
        { "Mary", 5, 6 },
        { "Joseph", 8, 7 },
        { "John", 4, 5 }
    };

    std::unordered_set<Player> player_set;

    for(auto player : player_vec)
        player_set.insert(player);
    
    for(auto player : player_set)
        std::cout << player << std::endl;
}