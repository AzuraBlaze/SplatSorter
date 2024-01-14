#ifndef SPLATSORTER_PLAYER_HPP
#define SPLATSORTER_PLAYER_HPP

#include <string>
#include <iostream>
#include <functional>

#include "Common.hpp"

class Player
{
    std::string name_m;
    int wins_m;
    int losses_m;

    public:

    Player()
    : name_m(), wins_m(0), losses_m(0) {}

    Player(const Player& other)
    : Player(other.name(), other.wins(), other.losses()) {}

    Player(const std::string& name, int wins, int losses)
    : name_m(name), wins_m(wins), losses_m(losses) {}

    Player(const std::string& name)
    : Player(name, 0, 0) {}


    const std::string& name() const;
    const std::string& name(const std::string& new_name);

    int wins() const;
    int wins(int new_wins);

    int losses() const;
    int losses(int new_losses);

    int rating() const;
};

std::ostream& operator<<(std::ostream& os, const Player& player);
bool operator==(const Player& lhs, const Player& rhs); //Compares names
bool operator<(const Player& lhs, const Player& rhs); //Compares ratings

template <>
struct std::hash<Player>
{
    std::size_t operator()(const Player& player) const
    {
        return std::hash<std::string>()(player.name());
    }
};

#endif /* SPLATSORTER_PLAYER_HPP */