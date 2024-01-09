#include "Player.hpp"

const std::string& Player::name() const
{
    return name_m;
}

const std::string& Player::name(const std::string& new_name)
{
    name_m = new_name;
    return name_m;
}


int Player::wins() const
{
    return wins_m;
}

int Player::wins(int new_wins)
{
    wins_m = new_wins;
    return wins_m;
}


int Player::losses() const
{
    return losses_m;
}

int Player::losses(int new_losses)
{
    losses_m = new_losses;
    return losses_m;
}


int Player::rating() const
{
    return wins_m - losses_m;
}


std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << "[ " << player.name() << " ]" << std::endl;
    os << "Wins: " << player.wins() << std::endl;
    os << "Losses: " << player.losses() << std::endl;

    return os;
}